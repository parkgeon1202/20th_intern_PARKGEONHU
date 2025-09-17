#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QTextStream>
#include <QStandardPaths>
#include <QFile>
#include <QMessageBox>

#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    keys(new QButtonGroup(this))
{
    ui->setupUi(this);



    savePath = QStandardPaths::writableLocation(  //파일을 저장할 경로 생성
                   QStandardPaths::DocumentsLocation) + "/message.txt";
    //키 버튼 등록
    keys->addButton(ui->pushButton_10, 10);    //그룹화를 시킴
    keys->addButton(ui->pushButton_11, 11);
    keys->addButton(ui->pushButton_12, 12);
    keys->addButton(ui->pushButton_30, 30);
    keys->addButton(ui->pushButton_29, 29);
    keys->addButton(ui->pushButton_28, 28);
    keys->addButton(ui->pushButton_26, 26);
    keys->addButton(ui->pushButton_25, 25);
    keys->addButton(ui->pushButton_24, 24);
    keys->addButton(ui->pushButton_23, 23);
    keys->addButton(ui->pushButton_21, BLANK_ID); // 동작 없는 공백 버튼
    keys->addButton(ui->pushButton_19, 19);
    keys->addButton(ui->pushButton_20, SPACE_ID); //  스페이스
    keys->addButton(ui->pushButton_9,  BACK_ID);  //  백스페이스

    connect(keys, SIGNAL(idClicked(int)), this, SLOT(handleKey(int)));


    // 영어(소문자)
    mapEnLower[10] = { ".",",","?","!" };
    mapEnLower[11] = { "a","b","c" };
    mapEnLower[12] = { "d","e","f" };
    mapEnLower[30] = { "g","h","i" };
    mapEnLower[29] = { "j","k","l" };
    mapEnLower[28] = { "m","n","o" };
    mapEnLower[26] = { "p","q","r","s" };
    mapEnLower[25] = { "t","u","v" };
    mapEnLower[24] = { "w","x","y","z" };
    mapEnLower[19] = { "," };
    mapEnLower[23] = { "<SHIFT>" };
    mapEnLower[BACK_ID]  = { "<BACK>" };
    mapEnLower[SPACE_ID] = { "<SPACE>" };


    // 영어(대문자)
    mapEnUpper = mapEnLower;
    for (auto &v : mapEnUpper)
        for (QString &s : v)
            if (s.size()==1 && s[0].isLetter()) s = s.toUpper();

    // 한글

    mapKo[10] = { "ㅣ" };
    mapKo[11] = { "." };
    mapKo[12] = { "ㅡ" };
    mapKo[30] = { "ㄱ","ㅋ" };
    mapKo[29] = { "ㄴ","ㄹ" };
    mapKo[28] = { "ㄷ","ㅌ" };
    mapKo[26] = { "ㅂ","ㅍ" };
    mapKo[25] = { "ㅅ","ㅎ" };
    mapKo[24] = { "ㅈ", "ㅊ" };
    mapKo[19] = { "한자" };
    mapKo[23] = { ".",",","?","!"  };
    mapKo[BACK_ID]  = { "<BACK>" };
    mapKo[SPACE_ID] = { "<SPACE>" };
    mapKo[BLANK_ID]= {"ㅇ", "ㅁ"};

    // 타이머
    multiTimer.setInterval(2000);
    multiTimer.setSingleShot(true);
    connect(&multiTimer, &QTimer::timeout, this, &MainWindow::commitTimeout);

    // 초기 레이아웃 즉 버튼 문자열 초기화
    setLayout(Layout::Ko); // 시작을 한글로 보고 싶다면 Ko, 아니면 EnLower
    connect(ui->pushButton_31, &QPushButton::clicked, this, &MainWindow::toggleLang);

    // 엔터키 누르면 파일 저장
    connect(ui->pushButton_27, &QPushButton::clicked, this, &MainWindow::saveToTxt);

    // 숫자와 버튼 포인터 해쉬로 묶어놓음
    btns = {
        {10, ui->pushButton_10}, {11, ui->pushButton_11}, {12, ui->pushButton_12},
        {30, ui->pushButton_30}, {29, ui->pushButton_29}, {28, ui->pushButton_28},
        {26, ui->pushButton_26}, {25, ui->pushButton_25}, {24, ui->pushButton_24},
        {23, ui->pushButton_23}, {BLANK_ID, ui->pushButton_21}, {19, ui->pushButton_19},
        {SPACE_ID, ui->pushButton_20}, {BACK_ID, ui->pushButton_9}
    };


    refreshKeyLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 입력창에 출력해주는 함수

void MainWindow::startOrCycle(int keyId, const QStringList &candidates) {
    QStringList seq = candidates;
    if (layout == Layout::Ko) {
        switch (keyId) {
        case 30: seq << QStringLiteral("ㄲ"); break; // ㄱ,ㅋ,ㄲ // ㄲ을 candidates에 추가
        case 28: seq << QStringLiteral("ㄸ"); break; // ㄷ,ㅌ,ㄸ
        case 26: seq << QStringLiteral("ㅃ"); break; // ㅂ,ㅍ,ㅃ
        case 25: seq << QStringLiteral("ㅆ"); break; // ㅅ,ㅎ,ㅆ
        case 24: seq << QStringLiteral("ㅉ"); break; // ㅈ,ㅊ,ㅉ
        default: break;
        }
    }
    //같은 버튼을 연속으로 눌렀을 때
    if (keyId == lastKeyId && multiTimer.isActive()) {
        cycleIndex = (cycleIndex + 1) % seq.size();
        replaceLast(seq.at(cycleIndex));   // .at()을 쓰면 디버그에서 범위 체크도 됨
        multiTimer.start();
        return;
    }

    //해당 버튼을 처음 눌렀을 때
    lastKeyId  = keyId;
    cycleIndex = 0;
    insertNew(seq.first());
    multiTimer.start();
}

//두 번 연속으로 눌렸을 때에 대한 커서 위치 처리
void MainWindow::replaceLast(const QString &ch) {
    QLineEdit *le = ui->lineEdit;
    if (!le) return;

    if (lastInsertPos < 0 || lastInsertPos > le->text().size()-1) {
        insertNew(ch);
        return;
    }
    //
    QString t = le->text();
    t.replace(lastInsertPos, 1, ch);
    le->setText(t);
    le->setCursorPosition(lastInsertPos + ch.size());
}

void MainWindow::insertNew(const QString &ch) {
    QLineEdit *le = ui->lineEdit;
    if (!le) return;
    int pos = le->cursorPosition();
    le->insert(ch);
    lastInsertPos = pos;
}

void MainWindow::commitTimeout() {
    lastKeyId = -1;
    cycleIndex = 0;
    lastInsertPos = -1;
}

//파일 저장

void MainWindow::saveToTxt()
{
    const QString text = ui->lineEdit->text().trimmed();
    if (text.isEmpty()) return;

    QFile f(savePath);


    QTextStream out(&f);
    out << text << '\n';
    out.flush();
    f.close();

    ui->lineEdit->clear();
}

// 라벨/토글

const QHash<int, QStringList>& MainWindow::currentMap() const {
    switch (layout) {
    case Layout::EnLower: return mapEnLower;
    case Layout::EnUpper: return mapEnUpper;
    case Layout::Ko:      return mapKo;
    }
    return mapEnLower; // fallback
}

//뭘 표시해야 할지 여기서 정함
QString MainWindow::labelFor(int id, const QHash<int, QStringList>& m) const {
    // 특수키 라벨
    if (id == 23){
        if(layout == Layout::Ko) return QStringLiteral(".,?!");
        return QStringLiteral("⬆");   // shift
    }
    if (id == BACK_ID)  return QStringLiteral("⬅");   // backspace
    if (id == SPACE_ID) return QStringLiteral("␣");   // space 표시
    if (id == BLANK_ID) {
        if(layout == Layout::Ko) return QStringLiteral("ㅇㅁ");
        return QString();             // 공백 버튼: 라벨 유지/빈칸
    }
    if (!m.contains(id) || m.value(id).isEmpty()) return QString();
    const QStringList &c = m.value(id);

    if (c.size() == 1) return c.front();

    QString lab;
    for (const QString &s : c) lab += s;
    return lab;
}
//여기서 버튼 문자열 초기화
void MainWindow::refreshKeyLabels() {
    const auto &m = currentMap();
    for (auto it = btns.constBegin(); it != btns.constEnd(); ++it) {
        const int id = it.key();
        if (QPushButton *b = it.value()) {
            const QString lab = labelFor(id, m);
            if (!lab.isEmpty())
                b->setText(lab);
        }
    }
}


void MainWindow::setLayout(Layout l) {
    layout = l;
    lastKeyId  = -1;
    cycleIndex = 0;
    lastInsertPos = -1;
    refreshKeyLabels();
}

void MainWindow::toggleLang() {
    if (layout == Layout::Ko) setLayout(Layout::EnLower);
    else setLayout(Layout::Ko);
}

void MainWindow::toggleShift() {
    if (layout == Layout::EnLower) setLayout(Layout::EnUpper);
    else if (layout == Layout::EnUpper) setLayout(Layout::EnLower);
}


//문자 삭제에 관한 커서위치와 출력 문자 처리
void MainWindow::doBackspace() {
    QLineEdit *le = ui->lineEdit;
    if (!le) return;

    int pos = le->cursorPosition();
    if (pos <= 0) return;

    QString t = le->text();
    t.remove(pos - 1, 1);
    le->setText(t);
    le->setCursorPosition(pos - 1);

    lastKeyId  = -1;
    cycleIndex = 0;
    lastInsertPos = -1;
}

void MainWindow::handleKey(int id) {
    const auto &m = currentMap();

    // SHIFT
    if (id == 23 && m.value(23).contains("<SHIFT>")) {
        toggleShift();
        return;
    }
    else if(id == 23 && m.value(23).contains(".")){
        startOrCycle(id, {".",",", "?", "!"});
        return;
    }
    // BACKSPACE
    if (id == BACK_ID) {
        doBackspace();
        commitTimeout();
        return;
    }
    //띄어쓰기 문자 버튼일 경우
    if (id == SPACE_ID) {
        if(cycleIndex==0){
            insertNew(" ");
            commitTimeout();
        }
        else{
            ui->lineEdit->setCursorPosition(ui->lineEdit->cursorPosition()+1);
            commitTimeout();
        }
        return;
    }

    if (id == BLANK_ID) {
        if(layout == Layout::Ko) startOrCycle(id, {"ㅇ","ㅁ"});
        return;
    }

    // 맵에 후보 없는 키는 무시
    if (!m.contains(id) || m.value(id).isEmpty()) return;

    // 기본 처리
    startOrCycle(id, m.value(id));
}
