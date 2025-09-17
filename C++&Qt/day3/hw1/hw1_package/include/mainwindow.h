#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QTimer>
#include <QHash>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }   // ui_mainwindow.h는 cpp에서 포함
QT_END_NAMESPACE

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleKey(int id); //버튼 눌렀을 때 발동됨
    void commitTimeout();   //타임아웃에 대한 슬롯 메서드
    void toggleLang();      // 한/영 키 바꾸기
    void toggleShift();     //시프트 키 눌렸을 때
    void saveToTxt();       //엔터키 눌렸을 때 저장

private:
    // ---- 고정 키 ID ----
    int BACK_ID  = 9;   //  뒤로가기 버튼 번호
    int SPACE_ID = 20;  // 스페이스 버튼 번호
    int BLANK_ID = 21;  // 동작 없는 공백 버튼 번호

    Ui::MainWindow *ui;
    QButtonGroup   *keys = nullptr; //버튼을 그룹화하여 한 곳에서 관리하기 위해 선언함
    QTimer          multiTimer;

    enum class Layout { EnLower, EnUpper, Ko }; //현재 한글인지 영어의 소문자인지 대문자인지 알 수 있는 상태 클래스
    Layout layout = Layout::EnLower;

    int  lastKeyId     = -1;
    int  cycleIndex    = 0;
    int  lastInsertPos = -1;

    QString savePath; //경로 설정을 위해

    // 키배열(멀티탭 후보)
    QHash<int, QStringList> mapEnLower, mapEnUpper, mapKo;  //버튼 번호와 해당 버튼의 문자열들과의 매치를 위해 선언

    // 버튼 포인터 테이블 (라벨 갱신용)
    QHash<int, QPushButton*> btns;  //버튼 번호와 버튼의 포인터와의 매치

    // 내부 유틸
    void setLayout(Layout l);   //버튼에 출력되는 문자열 초기화할 때 사용
    void startOrCycle(int keyId, const QStringList &candidates); //입력창에 출력할 때 사용
    void replaceLast(const QString &ch);   //2번 같은 키를 연속으로 누를 때 그 때 입력창에 실시간으로 기존 위치에서 문자 바꿔감
    void insertNew(const QString &ch);     //새 문자 삽입
    void doBackspace();                    //뒤로 가기 버튼 눌렀을 때 처리

    // 라벨 갱신
    void refreshKeyLabels();               //이걸로 버튼에 출력되는 문자열 초기화
    const QHash<int, QStringList>& currentMap() const;
    QString labelFor(int id, const QHash<int, QStringList>& m) const;
};

#endif // MAINWINDOW_H
