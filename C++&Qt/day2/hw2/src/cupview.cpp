#include "cupview.h"
#include <QPainter>
#include <QtMath>
#include <algorithm>

CupView::CupView(QWidget *parent) : QWidget(parent) {
    setMinimumSize(480, 320);

    pulseTimer.setInterval(2000);
    connect(&pulseTimer, &QTimer::timeout, this, &CupView::startSuck);
    pulseTimer.start(); //2초마다 빨기 시작

    //설정만 하고 대기
    animTimer.setInterval(30);
    connect(&animTimer, &QTimer::timeout, this, &CupView::onAnimTick);

    refillTimer.setInterval(20);
    connect(&refillTimer, &QTimer::timeout, this, &CupView::onRefillTick);
}

void CupView::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), Qt::white);

    // 컵의 영역 계산
    const int m = 40;
    QRectF area = rect().adjusted(m, m, -m, -m);
    QRectF cup(area.left()+80, area.top()+10, area.width()-160, area.height()-60);

    // 컵 외곽 그리기
    p.setPen(QPen(QColor(60,60,60), 2));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(cup, 10, 10);

    // 수위
    QRectF liquid = cup;
    liquid.setTop(liquid.bottom() - liquid.height()*level);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(230,90,60));
    p.drawRoundedRect(liquid.adjusted(2,2,-2,-2), 8, 8);

    // 빨대(수직)
    const double sx = cup.center().x();
    const double yBottom = cup.bottom() - 6;
    const double yAbove  = cup.top() - 40;
    p.setPen(QPen(QColor(100,100,100), 8, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(QPointF(sx, yBottom), QPointF(sx, yAbove));

    // 슬러그(빨리는 점)
    if (sucking) {
        double y = yBottom + (yAbove - yBottom) * progress; // 아래→위
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(230,90,60));
        p.drawEllipse(QPointF(sx, y), 6, 6);
    }
}

void CupView::startSuck() {
    if (sucking || refillTimer.isActive()) return;
    if (level <= 0.05) return;                 // 거의 바닥이면 빨지 않음
    level = std::max(0.0, level - 0.05);       // 한 번 빨 때 줄어드는 양
    progress = 0.0;
    sucking = true;
    animTimer.start();
    update();
}

void CupView::onAnimTick() {
    if (!sucking) { animTimer.stop(); return; }
    progress += 0.04;                           // 속도(값 키우면 빨라짐)
    if (progress >= 1.0) {
        progress = 1.0;
        sucking = false;
        animTimer.stop();
    }
    update();
}

void CupView::refill() {
    // 현재에서 30% 채우기(최대 가득)
    refillTarget = std::min(1.0, level + 0.3);
    if (refillTarget <= level) return;
    refillTimer.start();
}

void CupView::onRefillTick() {
    level += 0.01;                               // 채우는 속도
    if (level >= refillTarget) { //다 채우면 타이머 멈춰서 채우기 멈춤
        level = refillTarget;
        refillTimer.stop();
    }
    update();
}
