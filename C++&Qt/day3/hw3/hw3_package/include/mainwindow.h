#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QSpinBox>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<QRect> A_rect; //A*위젯의 각 그리드의 사각형 정보 모음
    std::vector<QRect> Dijk_rect; //데이크스트라 위젯의 각 그리드 사각형 정보 모음
    void get_grid(int val); //이 메서드로 그리드 사각형 생성하고 위의 벡터 초기화함
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* obj, QEvent* ev) override;
    void cal();
    std::vector<bool> A_selected;   //A*스타에서 마우스 찍힌 사각형 인덱스 저장하기 위해
    std::vector<bool> Dijk_selected; //데이크스트라에서 마우스로 찍힌 사각형 인덱스 저장하기 위해
    std::vector<bool> obstacle; //장애물로 뽑힌 사각형 인덱스 정보 저장하기 위해
    int start_index=-1; //시작점 사각형의 인덱스
    int end_index=-1; //끝점 사각형의 인덱스 값
private slots:

    void on_obstacle_button_clicked(); //obstacle 버튼 눌렸을 때
    void on_spinBox_valueChanged(int arg1); //스핀박스 값 바뀌었을 때

};
#endif // MAINWINDOW_H
