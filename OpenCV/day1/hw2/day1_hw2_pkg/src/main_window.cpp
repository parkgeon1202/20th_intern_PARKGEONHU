#include "../include/day1_hw2_pkg/main_window.hpp"
#include "ui_mainwindow.h"
#include <QFile>       

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->spinBox->setRange(1024, 65535);    // 내 포트(수신 바인드용)
    ui->spinBox->setValue(45500); //기본값 설정
    ui->spinBox_2->setRange(1024, 65535);  // 상대 포트(송신용)
    ui->spinBox_2->setValue(45500);

    
    udpSocket = new QUdpSocket(this); //소켓 생성
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readyRead); //읽는 슬롯으로 연결
    connect(ui->connection, &QPushButton::clicked, this, &MainWindow::on_connection_clicked);//연결 버튼 눌렀을 때 바인드
    connect(ui->publish,    &QPushButton::clicked, this, &MainWindow::on_publish_clicked); //publish 버튼 누르면 데이터 보냄
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event) {
    QMainWindow::closeEvent(event);
}

void MainWindow::on_connection_clicked() { //연결 눌렀을 때 바인드
    quint16 myPort = static_cast<quint16>(ui->spinBox->value()); //스핀박스 값 받아오기
    // bind하기, 아무 ip에서 들어오는 정보 다 받도록 설정, 공유 및 재사용
    udpSocket->bind(QHostAddress::AnyIPv4, myPort,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
 
}

void MainWindow::on_publish_clicked() { //publish 버튼 눌렀을 때 데이터 보냄
    QString peerIp   = ui->lineEdit->text().trimmed();     // 상대방 IP lineEdit에서 읽어오기
    quint16 peerPort = static_cast<quint16>(ui->spinBox_2->value()); // 상대 포트 값 받아오기

    QFile file(":/images/icon.png");   
    const QByteArray pngData = file.readAll(); //바이너리로 변환하여 다 가져와서 바이트 단위로 저장하기 위해 QByteArray사용
    file.close();

    udpSocket->writeDatagram(pngData, QHostAddress(peerIp), peerPort);

}

void MainWindow::readyRead() { //데이터 받아오는 작업
    while (udpSocket->hasPendingDatagrams()) { //받은 데이터 있다면
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize()); //받을 용량 늘림
        QHostAddress tempIp; //readDatagram 사용하기 위해 임시로 만듦
        quint16 tempPort;
        qint64 n = udpSocket->readDatagram(datagram.data(),datagram.size(),&tempIp, &tempPort);

        //받아온 바이트를 이미지로 생성하기 위해 
        cv::Mat img(1, static_cast<int>(n), CV_8UC3, datagram.data()); //r,g,b정보 3개 모두 담으며, 0~255 값으로 잡기 위해 
        
        showImage(img); //이제 사진을 화면에 출력
    }
}

void MainWindow::showImage(const cv::Mat &img) {//이미지 라벨에 출력하는 메서드 
 
    // OpenCV는 BGR이고  Qt는 RGB이기에 색상 올바르게 보이도록 변환
    cv::Mat rgb;
    cv::cvtColor(img, rgb, cv::COLOR_BGR2RGB); //플래그 변수를 통해 설정
    
    QImage qimg(rgb.data,rgb.cols,rgb.rows,rgb.step,QImage::Format_RGB888);//Mat를 QImage로 변환하는 부분
    // QLabel 사진 띄우기
    ui->picture_screen->setPixmap(QPixmap::fromImage(qimg));
}