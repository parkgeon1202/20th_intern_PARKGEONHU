#include "arm.h"
#include <QPainter>
#include <QtMath>

ArmView::ArmView(QWidget *parent) : QWidget(parent) { setMinimumSize(400,300); }

//bottom은 a0, middle은 a1, upper는 a2에 대응됨
void ArmView::setBottomAngle(int deg){ a0 = deg; update(); }
void ArmView::setMiddleAngle(int deg){ a1 = deg; update(); }
void ArmView::setUpperAngle(int deg){ a2 = deg; update(); }

void ArmView::paintEvent(QPaintEvent*) //이걸로 로봇팔 그림
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), Qt::white);

    // 베이스 기준점(바닥 가운데쯤)
    QPointF base(width()*0.5, height()*0.5);

    // 좌표계 세팅
    p.translate(base);

    // 1축(바닥 회전)
    p.save();
    p.rotate(-a0); // 시계/반시계는 필요에 맞춰 부호 변경
    p.setPen(QPen(Qt::black, 6));
    p.drawLine(QPointF(0,0), QPointF(L1,0)); // 첫 링크
    p.drawEllipse(QPointF(0,0), 8, 8);

    // 2축(중간 관절)
    p.translate(L1, 0);
    p.rotate(-a1);
    p.setPen(QPen(Qt::darkGray, 5));
    p.drawLine(QPointF(0,0), QPointF(L2,0));
    p.drawEllipse(QPointF(0,0), 7, 7);

    // 3축(끝 관절)
    p.translate(L2, 0);
    p.rotate(-a2);
    p.drawLine(QPointF(0,0), QPointF(L3,0));
    p.drawEllipse(QPointF(0,0), 6, 6);

    // 끝부분은 빨간색으로 표시
    p.setBrush(Qt::red);
    p.drawEllipse(QPointF(L3,0), 5, 5);

    p.restore();
}
int ArmView:: wrap361(int v) { v%=361; if(v<0) v+=361; return v; } //각도 범위 조정


void ArmView::stepBottom(int deltaDeg){ a0 = wrap361((int)a0 + deltaDeg); update(); } //각도 변화 최신화
void ArmView::stepMiddle(int deltaDeg){ a1 = wrap361((int)a1 + deltaDeg); update(); }
void ArmView::stepUpper(int deltaDeg) { a2 = wrap361((int)a2 + deltaDeg); update(); }

//getter 메서드 만듦
int ArmView::bottomAngle() const { return int(a0); }
int ArmView::middleAngle() const { return int(a1); }
int ArmView::upperAngle()  const { return int(a2); }
