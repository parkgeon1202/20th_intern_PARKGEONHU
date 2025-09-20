#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cupview.h"
#include <QVBoxLayout>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cupView = new CupView(this);
    auto *lay = new QVBoxLayout(ui->cupHost);
    lay->setContentsMargins(0,0,0,0);
    lay->addWidget(cupView);

    // 버튼 누르면 리필되는 메서드 호출
    connect(ui->refillButton, &QPushButton::clicked, cupView, &CupView::refill);
}

MainWindow::~MainWindow() { delete ui; }
