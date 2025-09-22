/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date August 2024
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/day2_hw1_pkg/main_window.hpp"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QRadioButton>
#include <QSlider>
#include <QApplication>   
Rect neon_rect, orange_rect, blue_rect, white_rect; 
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); //ui초기화 및 기본 세팅

    // QTimer 준비
    camTimer = new QTimer(this); //영상을 캡처하여 그 사진 정보를 반복적으로 빨리 가져오기 위해 QTimer 객체 생성
    connect(camTimer, &QTimer::timeout, this, &MainWindow::grabFrame); //타임아웃이 되면 현재 영상의 화면 사진 정보를 가져와서 이를 처리하고 화면에 띄움
    connect(ui->white_line, &QRadioButton::clicked, this, &MainWindow::white_click); //라디오 박스를 누르면 그 때 호출되는 슬롯 메서드
    connect(ui->blue_line, &QRadioButton::clicked, this, &MainWindow::blue_click); 
    connect(ui->neon_cone, &QRadioButton::clicked, this, &MainWindow::neon_click);
    connect(ui->orange_cone, &QRadioButton::clicked, this, &MainWindow::orange_click);
    connect(ui->hue_low, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed); //6개의 슬라이더를 하나의 슬롯 메서드로 연결해서 한 번에 처리하고자 함
    connect(ui->hue_high, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed);
    connect(ui->saturation_low, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed);
    connect(ui->saturation_high, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed);
    connect(ui->value_low, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed);
    connect(ui->value_high, &QSlider::sliderMoved, this, &MainWindow::any_slider_changed);


    ui->hue_high->setRange(0, 179); //슬라이더 값 범위 제한. 각 hsv의 범위로 맞춤
    ui->hue_low-> setRange(0,179);
    ui->saturation_high-> setRange(0, 255);
    ui->saturation_low-> setRange(0, 255);
    ui->value_high-> setRange(0, 255);
    ui-> value_low-> setRange(0, 255);
    //각각의 기본 hsv 초기값을 정의.각각의 색이 제일 잘 인식되는 low, high 범위로 설정  
    neon_slide.huelow = 20;
    neon_slide.huehigh = 30;
    neon_slide.satlow= 50;
    neon_slide.sathigh = 255;
    neon_slide.vallow= 100;
    neon_slide.valhigh = 255;
    orange_slide.huelow = 0;
    orange_slide.huehigh = 20;
    orange_slide.satlow= 50;
    orange_slide.sathigh = 255;
    orange_slide.vallow= 100;
    orange_slide.valhigh = 255;
    blue_slide.huelow = 100;
    blue_slide.huehigh = 130;
    blue_slide.satlow= 50;
    blue_slide.sathigh = 255;
    blue_slide.vallow= 50;
    blue_slide.valhigh = 255;
    white_slide.huelow = 0;
    white_slide.huehigh = 150;
    white_slide.satlow= 0;
    white_slide.sathigh = 10;
    white_slide.vallow= 240;
    white_slide.valhigh = 255;
    startCamera(); //카메라 오픈 및 초기화
}

MainWindow::~MainWindow() {
    delete ui;
    delete camTimer; //타이머 동적할당 한 것 해제 
}

void MainWindow::closeEvent(QCloseEvent* event) { 
    QMainWindow::closeEvent(event);
}

void MainWindow::startCamera() { 

    if (!cap.open(2)) return; //카메라 켜기
    //set메서드 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 360); //해상도 설정 
    cap.set(cv::CAP_PROP_FPS, 30); //fps 설정 1초에 30번 사진 찍음
 
    camTimer->start(33);  //타이머 시작 33ms 마다 타이머 호출. 같은 사진에 대해 여러번 호출하게 함으로써 분석을 여러 번 하게 하여 오류를 최소화하고자 함
}

void MainWindow::grabFrame() { 
    if (!cap.isOpened()) return; //카메라 열려있다는 것 확인

    Mat frame; 
    cap >> frame; //영상 속 사진 가져옴
    if (frame.empty()) return;
    Mat copy = frame.clone(); //깊은 복사를 시켜서 완전한 복사본을 만듦 사각형을 그린 영상을 따로 띄우기 위해  
    
    Mat neon, orange, blue_line1, white_line1; //생성할 바이너리 이미지 객체 선언
    //각각에 대한 바이너리 이미지 생성함수로 바이너리 이미지 생성
    neon = neon_cone(copy);
    orange= orange_cone(copy);
    blue_line1 = blue_line(copy);
    white_line1 = white_line(copy);
    //그 후 직사각형 그림을 copy 객체에 그리기 위해 draw_rectangle을 하여 바이너리 이미지를 인수로 넣어 매 색깔마다 추가해줌
    Mat temp= draw_rectangle(neon, copy, Scalar(0, 255, 255), "neon");
    temp= draw_rectangle(orange, temp, Scalar(0, 165, 255), "orange");
    temp= draw_rectangle(blue_line1, temp, Scalar(255, 0, 0), "blue");
    Mat second_screen= draw_rectangle(white_line1, temp, Scalar(255, 255, 255), "white");
    //사각형들을 그렸다면 lineEdit에 선을 기준으로 위 아래인지 왼쪽 오른쪽인지 계산하기 위해 전역으로 선언한 사각형들을 통해 계산함
    pos_cal();
    //opencv에서는 BGR인데 qt에 사진을 띄우기 위해서는 RGB로 해야 하므로 
    cvtColor(frame, frame, COLOR_BGR2RGB);
    cvtColor(second_screen, second_screen, COLOR_BGR2RGB);
    //Mat -> QImage로 변환
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QImage qimg_neon(neon.data, neon.cols, neon.rows, neon.step, QImage::Format_Grayscale8); //바이너리 이미지이기에 RGB포맷으로 변환하지 않음
    QImage qimg_orange(orange.data, orange.cols, orange.rows, orange.step, QImage::Format_Grayscale8);
    QImage qimg_blue_line(blue_line1.data, blue_line1.cols, blue_line1.rows, blue_line1.step, QImage::Format_Grayscale8);
    QImage qimg_white_line(white_line1.data, white_line1.cols, white_line1.rows, white_line1.step, QImage::Format_Grayscale8);
    QImage qimg_second_screen(second_screen.data, second_screen.cols, second_screen.rows, second_screen.step, QImage::Format_RGB888);
    // QLabel에 출력 
    ui->usb_cam->setPixmap(QPixmap::fromImage(qimg).scaled(ui->usb_cam->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->neon_display->setPixmap(QPixmap::fromImage(qimg_neon).scaled(ui->neon_display->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->orange_display->setPixmap(QPixmap::fromImage(qimg_orange).scaled(ui->orange_display->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->blue_display->setPixmap(QPixmap::fromImage(qimg_blue_line).scaled(ui->blue_display->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->white_display->setPixmap(QPixmap::fromImage(qimg_white_line).scaled(ui->white_display->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->find_object->setPixmap(QPixmap::fromImage(qimg_second_screen).scaled(ui->find_object->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    
    
}
//각각의 색깔에 대해 바이너리 이미지 생성
Mat MainWindow:: neon_cone(Mat neon){ 
  Mat temp, result;
  Scalar lower_yellow(neon_slide.huelow, neon_slide.satlow, neon_slide.vallow);
  Scalar upper_yellow(neon_slide.huehigh, neon_slide.sathigh, neon_slide.valhigh);
  cvtColor(neon, temp, COLOR_BGR2HSV);
  inRange(temp, lower_yellow, upper_yellow, result);
  return result;
}
Mat MainWindow:: orange_cone(Mat orange){
  Mat temp, result;
  Scalar lower_orange(orange_slide.huelow, orange_slide.satlow, orange_slide.vallow);
  Scalar upper_orange(orange_slide.huehigh, orange_slide.sathigh, orange_slide.valhigh);
  cvtColor(orange, temp, COLOR_BGR2HSV);
  inRange(temp, lower_orange, upper_orange, result);
  return result;
}
Mat MainWindow:: blue_line(Mat blue_line){
  Mat temp, result;
  Scalar lower_blue(blue_slide.huelow, blue_slide.satlow, blue_slide.vallow);
  Scalar upper_blue(blue_slide.huehigh, blue_slide.sathigh, blue_slide.valhigh);
  cvtColor(blue_line, temp, COLOR_BGR2HSV);
  inRange(temp, lower_blue, upper_blue, result);
  return result;
}
Mat MainWindow:: white_line(Mat white_line){
  Mat temp, result;
  Scalar lower_white(white_slide.huelow, white_slide.satlow, white_slide.vallow);
  Scalar upper_white(white_slide.huehigh, white_slide.sathigh, white_slide.valhigh);
  cvtColor(white_line, temp, COLOR_BGR2HSV);
  inRange(temp, lower_white, upper_white, result);
  return result;
}
//사각형 그리는 메서드, 추가로 해당 사각형을 전역 Rect객체에 저장하여 나중에 선 기준 위치 계산할 때 사용
Mat MainWindow::draw_rectangle(Mat mask, Mat origin, Scalar color, std::string s) {
 
  
  std::vector<std::vector<Point>> contours; //바이너리 이미지에 있는 점들 모두 얻기 위해 이차원으로 선언
  findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //findContours로 벡터 초기화

 
  Rect rect;
  for (size_t i = 0; i < contours.size(); ++i) { 
      double a = contourArea(contours[i]) //각각 요소의 영역 계산하여
      if (a > 600.0) {  //어느 정도 크기가 된다면 사각형 잡아주는 boundingRect를 호출하고 이걸로 사각형 그림 
        rect = boundingRect(contours[i]);    
        rectangle(origin, rect, color, 2); 
      }
  }
  //전역 변수 초기화 
  if(s== "neon") neon_rect= rect;
  else if(s=="orange") orange_rect = rect;
  else if(s=="blue") blue_rect = rect;
  else if(s=="white") white_rect = rect;
  return origin;
}
//꼬깔의 상대적 위치 계산하는 메서드
void MainWindow::pos_cal() {
    // Neon 콘 판별
  int cx = neon_rect.x + neon_rect.width / 2; //사각형의 중점을 기준으로 판단
  int cy = neon_rect.y + neon_rect.height / 2;

  // 세로 (blue_rect 기준)
  if (cy < blue_rect.y) {
      ui->neon_ver->setText("up");
  } 
  else if (cy > blue_rect.y + blue_rect.height) {
      ui->neon_ver->setText("down");
  } 
  else {
      ui->neon_ver->setText("center");
  }

  // 가로 (white_rect 기준)
  if (cx < white_rect.x) {
      ui->neon_hor->setText("left");
  } 
  else if (cx > white_rect.x + white_rect.width) {
      ui->neon_hor->setText("right");
  } 
  else {
      ui->neon_hor->setText("center");
  }

    //Orange 콘 판별 
  cx = orange_rect.x + orange_rect.width / 2; //중점을 기준으로 판단
  cy = orange_rect.y + orange_rect.height / 2;

  // 세로 (blue_rect 기준)
  if (cy < blue_rect.y) {
      ui->orange_ver->setText("up");
  } 
  else if (cy > blue_rect.y + blue_rect.height) {

      ui->orange_ver->setText("down");
  }
  else {
      ui->orange_ver->setText("center");
  }

  // 가로 (white_rect 기준)
  if (cx < white_rect.x) {
      ui->orange_hor->setText("left");
  } 
  else if (cx > white_rect.x + white_rect.width) {
      ui->orange_hor->setText("right");
  } 
  else {
      ui->orange_hor->setText("center");
  }
}
//해당되는 라디오 박스 눌렀을 때
void MainWindow:: white_click(){ 
   //해당 라디오 박스를 눌렀다면 그에 해당되는 slider 객체의 값을 바꾸도록 사인을 주기 위함
   blue_slide.flag = false;
   neon_slide.flag  = false;
   orange_slide.flag = false;

   white_slide.flag=true; 
   // 각 라디오 박스에 대한 슬라이더 상태를 다시 불러올 수 있도록 함
   ui->hue_high->setValue(white_slide.huehigh);
   ui->hue_low-> setValue(white_slide.huelow);
   ui->saturation_high->setValue(white_slide.sathigh);
   ui->saturation_low->setValue(white_slide.satlow);
   ui->value_high->setValue(white_slide.valhigh);
   ui->value_low->setValue(white_slide.vallow);
}
void MainWindow::blue_click() {

    white_slide.flag = false;
    neon_slide.flag  = false;
    orange_slide.flag = false;

    blue_slide.flag = true;

    ui->hue_high->setValue(blue_slide.huehigh);
    ui->hue_low ->setValue(blue_slide.huelow);
    ui->saturation_high->setValue(blue_slide.sathigh);
    ui->saturation_low ->setValue(blue_slide.satlow);
    ui->value_high->setValue(blue_slide.valhigh);
    ui->value_low ->setValue(blue_slide.vallow);
}

void MainWindow::neon_click() {
    white_slide.flag = false;
    blue_slide.flag  = false;
    orange_slide.flag = false;

    neon_slide.flag = true;

    ui->hue_high->setValue(neon_slide.huehigh);
    ui->hue_low ->setValue(neon_slide.huelow);
    ui->saturation_high->setValue(neon_slide.sathigh);
    ui->saturation_low ->setValue(neon_slide.satlow);
    ui->value_high->setValue(neon_slide.valhigh);
    ui->value_low ->setValue(neon_slide.vallow);
}

void MainWindow::orange_click() {
    white_slide.flag = false;
    blue_slide.flag  = false;
    neon_slide.flag  = false;

    orange_slide.flag = true;

    ui->hue_high->setValue(orange_slide.huehigh);
    ui->hue_low ->setValue(orange_slide.huelow);
    ui->saturation_high->setValue(orange_slide.sathigh);
    ui->saturation_low ->setValue(orange_slide.satlow);
    ui->value_high->setValue(orange_slide.valhigh);
    ui->value_low ->setValue(orange_slide.vallow);
}

void MainWindow::any_slider_changed(int val) {
    slider* t;
    //여기서 flag 변수 사용함 어떤 것의 hsv변수가 바뀌는 것인지에 대한 flag
    if(neon_slide.flag==true) t= &neon_slide;
    else if(orange_slide.flag==true) t= &orange_slide;
    else if(white_slide.flag==true) t= &white_slide;
    else if(blue_slide.flag==true) t= &blue_slide;

    // 슬라이더 값에서 읽기
    int hl = ui->hue_low->value();
    int hh = ui->hue_high->value();
    int sl = ui->saturation_low->value();
    int sh = ui->saturation_high->value();
    int vl = ui->value_low->value();
    int vh = ui->value_high->value();
    //이를 해당되는 객체의 멤버에 넣어줌
    t->huelow = hl;   
    t->huehigh = hh;
    t->satlow = sl;   
    t->sathigh = sh;
    t->vallow = vl;   
    t->valhigh = vh;
}


   