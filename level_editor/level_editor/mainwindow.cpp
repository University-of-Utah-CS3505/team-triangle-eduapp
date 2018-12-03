#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSpinBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model m(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinButton_clicked()
{

    QSpinBox * box = new QSpinBox();
    box->setRange(0,5);
    for(int i =0; i < ui->spinBox->value(); i++){
        for(int j =0; j < ui->spinBox->value(); j++){
            QSpinBox *box = new QSpinBox();
            box->setObjectName(QString::number(i) + QString("#") + QString::number(j));
            connect(box,SIGNAL(valueChanged(int)), this, SLOT(update_color(int)));
            ui->gridLayout->addWidget(box,i,j);
        }
    }
}

void MainWindow::update_color(int col){
    QSpinBox* box = qobject_cast<QSpinBox *>(sender());
    QPalette pal = box->palette();


    box->setPalette(pal);
    if (col == 1){
        pal.setColor(box->backgroundRole(), Qt::blue);
    }
    else if (col == 2){
        pal.setColor(box->backgroundRole(), Qt::green);
    }
    else{
        pal.setColor(box->backgroundRole(), Qt::black);
    }
    box->setPalette(pal);
}
