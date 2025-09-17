#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QHostAddress>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QTimer;
QT_END_NAMESPACE

class DrawingCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStart();
    void onReset();
    void onConnect();
    void onReadyRead();
    void onScoresUpdated(double s1, double s2, double coop);
    void onStatus(const QString &msg);
    void onTick();

private:
    Ui::MainWindow *ui;
    DrawingCanvas *canvas;

    // 네트워크
    QUdpSocket *udp = nullptr;
    QHostAddress peerAddr;
    quint16 localPort = 45454, peerPort = 45455;
    bool connected = false;
    int myRole = 1;

    // 타임어택
    qint64 startEpochMs = 0, endEpochMs = 0;
    int durationMs = 60000;
    bool timerRunning = false;
    QTimer *gameTimer = nullptr;

    // ★ 누락된 함수 선언들 추가
    void setupConnections();
    void setupTimer();
    void sendJson(const QJsonObject& obj);
    void startCountdownLocal(qint64 epochMs, int durMs);
    void stopCountdown(bool byTimeout);
    void updateTimerLabel(qint64 nowMs);
    QString fmtTimeMs(qint64 ms);
    void finalizeAndBroadcastResult(const QString& reasonHint = "");
};

#endif // MAINWINDOW_H
