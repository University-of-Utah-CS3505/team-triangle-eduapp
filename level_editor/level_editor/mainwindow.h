#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"model.h"
#include <QMainWindow>
#include <QSpinBox>
#include <QLabel>

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


    void on_actionsave_triggered();

    void on_tank_button_clicked();



    void on_remove_object_button_clicked();
    void on_loc1_changed(int loc1);
    void on_loc2_changed(int loc2);

    void on_tree_button_clicked();

    void on_target_button_clicked();

private:
    Ui::MainWindow *ui;
    //const model m();
    void save();
    model m;
    std::vector<QSpinBox*> list_of_boxes;
    std::vector<std::tuple<QLabel*,QSpinBox*,QSpinBox*>> object_layout_map;
    void add_object(std::string s);
};

#endif // MAINWINDOW_H
