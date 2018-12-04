#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : m(0),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinButton_clicked()
{
    m.resize_array(ui->spinBox->value());
    for(QSpinBox* item : list_of_boxes){
        ui->gridLayout->removeWidget(item);
        item->hide();
        item->deleteLater();
    }
    list_of_boxes.clear();

    QSpinBox * box = new QSpinBox();
    box->setRange(0,5);
    for(int i =0; i < ui->spinBox->value(); i++){
        for(int j =0; j < ui->spinBox->value(); j++){
            QSpinBox *box = new QSpinBox();
            box->setObjectName(QString::number(i) + QString("#") + QString::number(j));
            connect(box,SIGNAL(valueChanged(int)), this, SLOT(update_color(int)));
            ui->gridLayout->addWidget(box,i,j);
            list_of_boxes.emplace_back(box);
        }
    }
}

void MainWindow::update_color(int col){
    QSpinBox* box = qobject_cast<QSpinBox *>(sender());
    QPalette pal = box->palette();


    box->setPalette(pal);
    if (col == 1){

        pal.setColor(box->backgroundRole(), Qt::blue);
        box->setStyleSheet("QSpinBox {background-color: blue;}");
    }
    else if (col == 2){
        pal.setColor(box->backgroundRole(), Qt::green);
        box->setStyleSheet("QSpinBox {background-color: green;}");
    }
    else{
        pal.setColor(box->backgroundRole(), Qt::black);
        box->setStyleSheet("QSpinBox {background-color: black;}");
    }
    box->setPalette(pal);
}
