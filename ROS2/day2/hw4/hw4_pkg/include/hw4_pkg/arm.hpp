// armview.h
#pragma once
#include <QWidget>

class ArmView : public QWidget {
    Q_OBJECT
public:
    explicit ArmView(QWidget *parent = nullptr);
    void setBottomAngle(int deg); //해당 각도로 팔 초기화함 setter
    void setMiddleAngle(int deg); //스핀 박스로 값 바꿀 때 호출되는 메서드
    void setUpperAngle(int deg);  //호출되어 각도 초기화함


private:
    double a0=0, a1=0, a2=0;     // bottom, middle, upper관련 관절 각도
    double L1=120, L2=100, L3=80; // 각 팔의 길이
    void paintEvent(QPaintEvent *) override;
};
