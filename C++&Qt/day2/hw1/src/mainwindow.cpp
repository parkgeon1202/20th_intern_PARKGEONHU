#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "arm.h"
#include "QVBoxLayout"
#include <QPushButton>
#include <iostream>
#include <QFile>                      //파일 처리
#include <QTextStream>
#include <QStandardPaths> // 슬라이더/스핀박스 동기화
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 스핀박스 최대값 360
    ui->spinBox->setRange(0, 360);             //최대 두자리 수여서 360까지 값을 받을 수 있도록 설정
    ui->spinBox_2->setRange(0, 360);
    ui->spinBox_3->setRange(0, 360);


    armView = new ArmView(this);               //동적할당하여 객체 생성하여 이 객체로 팔 조절
    auto *layout = new QVBoxLayout(ui->armViewHost); //로봇팔을 위젯 위에 그리기 위한 설정
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(armView);



    //버튼 설정 시그널과 슬롯 연결
    connect(ui->bottom_clock,        &QPushButton::clicked, this, &MainWindow::on_bottom_clicked);
    connect(ui->bottom_counterclock, &QPushButton::clicked, this, &MainWindow::on_bottom_counter_clicked);

    connect(ui->middle_clock,        &QPushButton::clicked, this, &MainWindow::on_middle_clicked);
    connect(ui->middle_counterclock, &QPushButton::clicked, this, &MainWindow::on_middle_counter_clicked);

    connect(ui->upper_clock,         &QPushButton::clicked, this, &MainWindow::on_upper_clicked);
    connect(ui->upper_counterclock,  &QPushButton::clicked, this, &MainWindow::on_upper_counter_clicked);


    //타이머 연결
    connect(&bottomTimer, &QTimer::timeout, this, &MainWindow::onBottomTick);
    connect(&middleTimer, &QTimer::timeout, this, &MainWindow::onMiddleTick);
    connect(&upperTimer,  &QTimer::timeout, this, &MainWindow::onUpperTick);
    //connect(&saveTimer, &QTimer::timeout, this, &MainWindow::Save);
    savePath = QStandardPaths::writableLocation(  //파일을 저장할 경로 생성
                   QStandardPaths::DocumentsLocation)
               + "/robot_arm_state.txt";

    // 자동 저장 주기 설정 2초마다 슬롯 함수 호출
    connect(&saveTimer, &QTimer::timeout, this, &MainWindow::saveToTxt); //2초마다 자동 txt파일에 정보 업데이트하도록 만듦
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadFromTxt); //버튼 누르면 정보 가져오게 함
    saveTimer.start(2000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//외곽 틀을 만들기 위함
void MainWindow::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}


//spin Box에 대한 슬롯 함수 정의 입력 받은 각도 값으로 그만큼 회전
void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    armView->setMiddleAngle(arg1);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    armView->setBottomAngle(arg1);
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    armView->setUpperAngle(arg1);
}

//버튼 누르면 타이머가 시작되어 움직이게 되는데 타이머를 시작해주는 메서드
void MainWindow::toggleTimer(QTimer& t, int& dirVar, int newDir) {
    if (t.isActive() && dirVar == newDir) { t.stop(); return; } // 같은 방향이면 정지 즉 다시 그 버튼 누르면 정지
    dirVar = newDir;
    t.start(intervalMs);
}

// 버튼 눌렸을 때 호출되는 슬롯 메서드. ArmView를 직접 굴릴 방향 지정
void MainWindow::on_bottom_clicked()         { toggleTimer(bottomTimer, bottomDir, +1); }
void MainWindow::on_bottom_counter_clicked() { toggleTimer(bottomTimer, bottomDir, -1); }

void MainWindow::on_middle_clicked()         { toggleTimer(middleTimer, middleDir, +1); }
void MainWindow::on_middle_counter_clicked() { toggleTimer(middleTimer, middleDir, -1); }

void MainWindow::on_upper_clicked()          { toggleTimer(upperTimer,  upperDir,  +1); }
void MainWindow::on_upper_counter_clicked()  { toggleTimer(upperTimer,  upperDir,  -1); }

// ArmView 메서드 직접 호출. 타이머가 시작되어서 timeout이 되었을 때 호출되는 슬롯 메서드
void MainWindow::onBottomTick() { armView->stepBottom(bottomDir * 2); } //20ms당 2도 회전
void MainWindow::onMiddleTick() { armView->stepMiddle(middleDir * 2); }
void MainWindow::onUpperTick()  { armView->stepUpper(upperDir  * 2); }

void MainWindow::saveToTxt() //txt파일에 각도, 방향 저장함
{
    QFile f(savePath);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Save fail", "파일 열기 실패: " + savePath);
        return;
    }
    QTextStream out(&f);
    // 형식: a0 a1 a2 bottomDir middleDir upperDir
    out << armView->bottomAngle() << ' '
        << armView->middleAngle() << ' '
        << armView->upperAngle()  << ' '
        << bottomDir << ' ' << middleDir << ' ' << upperDir << '\n';
    f.close();
    // qDebug() << "Saved to" << savePath;
}

void MainWindow::loadFromTxt() //정보를 가져오는 함수. bring버튼 누르면 정보 가져와서 저장했던 그 상태로 되돌려줌
{
    QFile f(savePath);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Load fail", "파일 열기 실패: " + savePath);
        return;
    }
    QTextStream in(&f);
    int a0, a1, a2, bdir, mdir, udir;
    in >> a0 >> a1 >> a2 >> bdir >> mdir >> udir;
    f.close();

    // 각도/방향 복원
    armView->setBottomAngle(a0);
    armView->setMiddleAngle(a1);
    armView->setUpperAngle(a2);
    bottomDir = bdir; middleDir = mdir; upperDir = udir;


    //되돌린 상태에서 정지
    bottomTimer.stop();
    middleTimer.stop();
    upperTimer.stop();

}

