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

    int bottomAngle()const;  //각도값을 얻어오는 getter
    int middleAngle()const;
    int upperAngle()const;

    void stepBottom(int deltaDeg); //자동으로 돌아가는 버튼을 눌렀을 때 그 때 자동으로 각도를 초기화하는 함수
    void stepMiddle(int deltaDeg);
    void stepUpper(int deltaDeg);


private:
    double a0=0, a1=0, a2=0;     // bottom, middle, upper관련 관절 각도
    double L1=120, L2=100, L3=80; // 각 팔의 길이
    int wrap361(int v); //메서드 내부에서 호출하기 때문에 private로 은닉화
    void paintEvent(QPaintEvent *) override;
};
