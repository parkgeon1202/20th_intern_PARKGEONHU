#pragma once
#include <QMainWindow>
#include <QUdpSocket>
#include <QLabel>
#include <QHostAddress>
#include <QCloseEvent>
#include <opencv2/opencv.hpp> //opencv 사용
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }  
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_connection_clicked();   // 연결 버튼
    void on_publish_clicked(); // publish 버튼
    void readyRead();  // UDP 수신했을 때 콜백 함수


private:
    Ui::MainWindow *ui = nullptr;
    QUdpSocket *udpSocket = nullptr;     //소켓 다루는 포인터  
    void showImage(const cv::Mat &img);     //라벨에 이미지 출력하는 메서드
};
