#include "../include/mainwindow.h"
#include "ui/ui_mainwindow.h"
#include <QPushButton>
#include <QRect>
#include <QMouseEvent>
#include <ctime>
#include <cstdlib>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setRange(5, 30); //스핀박스 값 범위 제한
    ui->widget->installEventFilter(this); // 발생하는 마우스 클릭 이벤트를 MainWindow클래스의 이벤트로 끌고 오기 위해
    ui->widget_2->installEventFilter(this); //widget의 클래스에 대해 따로 클래스 정의나 오버라이딩을 하고 싶지 않고 MainWindow에서 모든 처리를 하고자 했음
    srand((unsigned)time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow:: cal(){ //정해진 출발점과 끝점의 정보를 통해 각각의 알고리즘을 사용하여 확정난 노드, 길을 색으로 색칠하는 메서드

}
void MainWindow::on_obstacle_button_clicked() //obstacle 버튼 누르면 그리드의  30%로 랜덤으로 해당 그리드 인덱스에 색칠하는 메서드
{

    int size = ui->spinBox->value(); //스핀 박스의 값 받아서
    obstacle.resize(size*size, false); //벡터 사이즈 설정
    int cnt=0;
    while(cnt<obstacle.size()*0.3){ //30%로 설정
        int i=rand()%obstacle.size(); //랜덤 생성하고
        if(obstacle[i]==false){ //만약 같은 거 걸릴 시 거름
            obstacle[i] = true;
          cnt++;
        }


    }
    update(); //색칠
}



void MainWindow:: get_grid(int val){ //그리드 생성하고 A_rect, Dijk_rect 초기화해줌

        QRect r = ui->widget->rect(); //widget의 width, height 정보를 받아오기 위해 QWidget::rect 메서드를 씀
        A_rect.clear(); //스핀박스 값이 바뀌면 get_grid가 매번 호출되기에 그 때마다 벡터 내용 비워주기
        Dijk_rect.clear();
        for (int i=0; i<val; i++) {
            for (int j=0; j<val; j++) {
                QRect rect(j*r.width()/val, i*r.height()/val, r.width()/val, r.height()/val); //좌상단 좌표와 너비, 높이를 전체 중에 가로 세로 칸 개수로 나눠서 좌표 잡음
                A_rect.push_back(rect);  //그리고 이를 저장해줌 이 때는 상대적인 좌표이기에, ui->widget에 대해서 rect를 해도 같은 크기의 로컬 좌표이기에
                Dijk_rect.push_back(rect); //한꺼번에 처리해도 괜찮음
            }
        }
        A_selected.assign(A_rect.size(), false);  //같은 크기만큼 false로 초기화하여 벡터 초기화
        Dijk_selected.assign(Dijk_rect.size(), false);
        update();
}

void MainWindow::paintEvent(QPaintEvent*) {  //색칠하는 메서드 오버라이딩
    QPainter p(this); //MainWindow에 대해 칠함
    p.setPen(Qt::white); //흰색으로 칠함 검은색 배경이어서


    QPoint offA = ui->widget->mapTo(this, QPoint(0,0)); //MainWindow 배경(부모 좌표계)에 대해 칠하기에 이를 widget의 좌표계를 파악하기 위해 widget의 좌상단 위치 파악
    p.save(); //현 상태 저장
    p.translate(offA); //해당 좌표로 이동

    for (int i=0; i<(int)A_rect.size(); ++i) {
        if(i<obstacle.size()&&obstacle[i]){ //장애물인 경우 검은색으로 칠하기
            p.fillRect(A_rect[i].adjusted(1,1,-1,-1), QColor(255,255,255));
        }
        if (A_selected[i]) {  //마우스 클릭 받은 사각형의 경우
             p.fillRect(A_rect[i].adjusted(1,1,-1,-1), QColor(255,255,0,120)); //색 칠하기
        }
         p.drawRect(A_rect[i].adjusted(0,0,-1,-1)); //그리드 사각형 정보대로 네모 그리기
    }

    p.restore(); //다시 되돌리기

    //데이크 스트라의 위젯에 대해서도 똑같이 적용
    QPoint offD = ui->widget_2->mapTo(this, QPoint(0,0));
    p.save();
    p.translate(offD);

    for (int i=0; i<(int)Dijk_rect.size(); ++i) {
        if(i< obstacle.size()&&obstacle[i]){
             p.fillRect(Dijk_rect[i].adjusted(1,1,-1,-1), QColor(255,255,255));
        }
         if ( Dijk_selected[i]) {
            p.fillRect(Dijk_rect[i].adjusted(1,1,-1,-1), QColor(0,180,255,120));
        }
         p.drawRect(Dijk_rect[i].adjusted(0,0,-1,-1));
    }

     p.restore();

}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    get_grid(arg1); //스핀 박스 값 바뀌면 다시 그리드 계산해서 그려야 하므로 get_grid 호출
}

bool MainWindow::eventFilter(QObject* obj, QEvent* ev) {

    if (ev->type() == QEvent::MouseButtonPress) { //오버라이딩하고, 받은 이벤트가 MouseButtonPress인 경우에만
        auto* me = static_cast<QMouseEvent*>(ev);


        if (obj == ui->widget) { //A*의 위젯을 누른 경우
            QPoint pt = me->pos(); // 이벤트가 발생한 객체의 widget 내부 좌표계로 반환함, 마우스 클릭된 widget내의 점
            for (int i=0; i<(int)A_rect.size(); ++i) {
                if (A_rect[i].contains(pt)) { //QRect의 멤버함수를 통해 그 점이 해당 사각형에 포함되는지 확인
                    A_selected[i] = !A_selected[i]; // 토글, 같은 사각형을 두 번 누른 경우에 대한 예외처리
                    Dijk_selected[i] = !Dijk_selected[i]; //같이 토글되도록 하여 데이크 스트라 위젯에서도 해당되는 사각형에 찍도록 함 시작점, 끝점이 같기 때문
                    if(start_index<0) start_index=i; //시작점, 끝점 저장
                    else if(end_index<0) end_index=i;
                    update(); //마우스 클릭된 거 색칠
                    if(start_index>=0 &&end_index>=0&& start_index!= end_index){
                        cal(); //만약 시작점, 끝점이 다 정해지면 이제 cal메서드로 알고리즘 연산
                    }
                    return true;
                }
            }

        }

        // 데이크 스트라의 위젯의 경우에도 똑같이 적용
        if (obj == ui->widget_2) { //만약 데이크 스트라의 위젯을 누른 경우
            QPoint pt = me->pos();
            for (int i=0; i<(int)Dijk_rect.size(); ++i) {
                if (Dijk_rect[i].contains(pt)) {
                    A_selected[i] = !A_selected[i];
                    Dijk_selected[i] = !Dijk_selected[i];
                    if(start_index<0) start_index=i;
                    else if(end_index<0) end_index=i;
                    update();
                    if(start_index>=0 &&end_index>=0&& start_index!= end_index){
                        cal();
                    }
                    return true;
                }
            }

        }

    }
    return false;
}

