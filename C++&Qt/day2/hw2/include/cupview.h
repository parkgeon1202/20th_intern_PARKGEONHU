#pragma once
#include <QWidget>
#include <QTimer>

class CupView : public QWidget {
    Q_OBJECT
public:
    explicit CupView(QWidget *parent=nullptr);

public slots:
    void refill();                // 버튼에서 호출

private slots:
    void startSuck();             // 2초마다 빨기
    void onAnimTick();            // 슬러그 이동
    void onRefillTick();          // 리필 애니메이션

private:
    // 상태
    double level = 0.8;           // 0.0~1.0 : 컵 안의 수위
    bool   sucking = false;       // 빨기 중 여부
    double progress = 1.0;        // 슬러그 이동 진행도(0~1)
    double refillTarget = 1.0;    // 끝까지 리필 되도록 설정
    void paintEvent(QPaintEvent*) override;
    // 타이머
    QTimer pulseTimer;            // 2초 주기 빨기
    QTimer animTimer;             // 슬러그 이동 30ms
    QTimer refillTimer;           // 리필 20ms
};
