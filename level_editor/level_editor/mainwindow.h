#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"model.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinButton_clicked();
    void update_color(int color);

private:
    Ui::MainWindow *ui;
    //const model m();
};

#endif // MAINWINDOW_H
