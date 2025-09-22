/**
 * @file /include/day2_hw1_pkg/main_window.hpp
 *
 * @brief Qt based gui for %(package)s.
 *
 * @date August 2024
 **/

#ifndef day2_hw1_pkg_MAIN_WINDOW_H
#define day2_hw1_pkg_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/
#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <opencv2/opencv.hpp>
namespace Ui { class MainWindow; }
using namespace cv;
/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
//구조체 선언함. 각각의 라디오 버튼에 대한 슬라이더 값 정보를 기억하기 위해 
struct slider{
    bool flag; int huehigh; int huelow;
    int sathigh; int satlow; int valhigh; int vallow;
};
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void startCamera();   // 카메라 오픈 및 초기화 메서드
    void grabFrame(); // 한 프레임씩 읽어서 라벨에 사진 띄우기
    void white_click();// white_line 라디어 박스 눌렀을 때
    void blue_click();  //blue_line 라디오 박스 눌렀을 때  
    void neon_click(); //neon_cone 라디오 박스 눌렀을 때
    void orange_click(); //orange_cone 라디오 박스 눌렀을 때
    void any_slider_changed(int val); //슬라이더 바뀌었을 때,, 각각의 슬라이더를 처리하기에는 너무 슬롯 메서드가 많아져서 모든 슬라이더를 한 번에 처리
private:
    Ui::MainWindow *ui = nullptr;
    QTimer *camTimer = nullptr; //한 프레임 읽을 때의 타이머
    VideoCapture cap; //카메라 영상 정보 가져오기 위해

    //다른 라벨 화면에 띄워야 할 사진 정보를 가공하기 위해 선언, 바이너리 이미지 생성
    Mat neon_cone(Mat neon);  
    Mat orange_cone(Mat orange);
    Mat blue_line(Mat blue_line);
    Mat white_line(Mat white_line);
    //네모 그리는 메서드
    Mat draw_rectangle(Mat mask, Mat origin, Scalar color,std::string s); //lineEdit에 출력할 up, down, right, left 등을 판단하기 위해 콘의 위치를 계산함
    void pos_cal();
    //각각의 라디오 버튼의 슬라이더 정보를 기억하기 위해 각각의 대응되는 객체 선언
    slider white_slide;
    slider blue_slide;
    slider neon_slide;
    slider orange_slide;
};


#endif  // day2_hw1_pkg_MAIN_WINDOW_H
