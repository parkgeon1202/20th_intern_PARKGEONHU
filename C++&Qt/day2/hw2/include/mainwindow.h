#pragma once
#include <QMainWindow>
class CupView;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    CupView *cupView = nullptr;
};
