#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class ArmView;
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

private slots:

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    //스핀 박스 슬롯 메서드
    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    //버튼 눌렸을 때의 슬롯 메서드
    void on_bottom_clicked();

    void on_bottom_counter_clicked();

    void on_middle_clicked();

    void on_middle_counter_clicked();

    void on_upper_clicked();

    void on_upper_counter_clicked();

    //타임아웃되었을 때
    void onBottomTick();
    void onMiddleTick();
    void onUpperTick();
    //타임아웃되어 저장할 때 호출되는 슬롯메서드
    void saveToTxt();              // 저장
    //bring버튼이 눌렸을 때 호출되는 슬롯메서드
    void loadFromTxt();            // 불러오기 (옵션)

    //void Save();
private:
    Ui::MainWindow *ui;
    ArmView* armView;
    QTimer bottomTimer, middleTimer, upperTimer, saveTimer;
    int bottomDir=0, middleDir=0, upperDir=0; // +1 시계, -1 반시계
    QString savePath;              // 저장 파일 경로

    int intervalMs = 20; // 틱 간격(ms)

    void toggleTimer(QTimer& t, int& dirVar, int newDir);
};
#endif // MAINWINDOW_H
