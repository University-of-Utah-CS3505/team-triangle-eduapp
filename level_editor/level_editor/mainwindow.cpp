#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

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
    //std::cout << box->objectName().split('#').first().toUtf8().constData() << box->objectName().split('#').last().toUtf8().constData()<< std::endl;
    m.set_item(box->objectName().split('#').first().toInt(),box->objectName().split('#').last().toInt(),box->value());


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
        pal.setColor(box->backgroundRole(), Qt::white);
        box->setStyleSheet("QSpinBox {background-color: black;}");
    }
    box->setPalette(pal);
}

void MainWindow::on_actionsave_triggered()
{
    m.save_model();
}

void MainWindow::on_tank_button_clicked()
{
    add_object("spawn");

}

void MainWindow::add_object(std::string s){
    QLabel* label =  new QLabel;

    QSpinBox* loc1 =  new QSpinBox;
    loc1->setObjectName(QString::number(object_layout_map.size()));
    connect(loc1,SIGNAL(valueChanged(int)), this, SLOT(on_loc1_changed(int)));

    QSpinBox* loc2 = new QSpinBox;
    loc1->setObjectName(QString::number(object_layout_map.size()));
    connect(loc2,SIGNAL(valueChanged(int)), this, SLOT(on_loc2_changed(int)));

    label->setText(QString::fromUtf8(s.c_str()));
    std::tuple<QLabel*,QSpinBox*,QSpinBox*> tup (label,loc1,loc2);
    object_layout_map.emplace_back(tup);
    ui->object_label_area->addWidget(label);
    ui->object_loc_1_area->addWidget(loc1);
    ui->object_loc_2_area->addWidget(loc2);
    m.add_object(s, object_layout_map.size(), object_layout_map.size());
}


void MainWindow::on_remove_object_button_clicked()
{
    //check is spinbox is giving a value out of bounds
    int val = ui->remove_object_box->value();
    if(val >= object_layout_map.size()){
        ui->remove_object_box->setValue(0);
        ui->label_remove_dynamic->setText("Out of bounds! Set spinbox to 0");
        return;
    }
    //hides (effectively removes) elements then marks for deletion.
    std::tuple<QLabel*,QSpinBox*,QSpinBox*> tup = object_layout_map[val];
    std::get<0>(tup)->hide();std::get<1>(tup)->hide();std::get<2>(tup)->hide();
    std::get<0>(tup)->deleteLater();std::get<1>(tup)->deleteLater();std::get<2>(tup)->deleteLater();
    object_layout_map.erase(object_layout_map.begin()+val);
    //Update location indexes for location map, because they are only set in the add object method.
    for(int i = val;i<object_layout_map.size(); i++){
        tup = object_layout_map[i];
        std::get<1>(tup)->setObjectName(QString::number(i));
        std::get<1>(tup)->setObjectName(QString::number(i));
    }
    m.remove_object(val);
}

void MainWindow::on_loc1_changed(int a){
    int b = sender()->objectName().toInt();
    ui->label_remove_dynamic->setText("LELEL");
    m.update_loc1(b,a);
}
void MainWindow::on_loc2_changed(int a){
    int b = sender()->objectName().toInt();
    m.update_loc1(b,a);
}



void MainWindow::on_tree_button_clicked()
{
    add_object("solid");
}

void MainWindow::on_target_button_clicked()
{
    add_object("target");
}
