#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "QDir"
#include "QDebug"
#include <QPixmap>
#include <QPair>
#include <QMap>

MainWindow::MainWindow(QWidget *parent) : m(0),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater1.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadEast.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadNorth.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadCornerUR.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadCornerLL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadCornerUL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadCornerLR.png");

    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadCrossing.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadSplitE.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadSplitN.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadSplitS.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileWater_roadSplitW.png");

    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand1.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand2.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadEast.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadNorth.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadCornerUR.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadCornerLL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadCornerLR.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadCornerUL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadCrossing.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadSplitE.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadSplitN.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadSplitS.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileSand_roadSplitW.png");

    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass1.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass2.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadEast.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadNorth.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUR.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerLR.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadCornerUL.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadCrossing.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadSplitE.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadSplitN.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadSplitS.png");
    image_paths.emplace_back("../assets/Tanks/PNG/DefaultSize/tileGrass_roadSplitW.png");

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
    list_of_images.clear();
    ui->scrollAreaWidgetContents->setLayout(ui->gridLayout);
    QSpinBox * box = new QSpinBox();

    qDebug() << QDir::currentPath();
    box->setRange(0,5);
    int count = 0;
    for(int i =0; i < ui->spinBox->value(); i++){
        for(int j =0; j < ui->spinBox->value(); j++){

            std::vector<int> _current_pos;
            _current_pos.emplace_back(count);
            _current_pos.emplace_back(j);

            QLabel* image = new QLabel();
            QPixmap pix("../assets/Tanks/PNG/DefaultSize/tileWater1.png");
            //bool f =pix.load();

            image->setPixmap(pix);
            image->setObjectName(QString::number(i) + QString("+") + QString::number(j));

            ui->gridLayout->addWidget(image,count,j);

            map.insert(image, _current_pos);
            list_of_images.emplace_back(image);

            QSpinBox *box = new QSpinBox();
            box->setRange(0,37);
            box->setObjectName(QString::number(i) + QString("#") + QString::number(j));
            connect(box,SIGNAL(valueChanged(int)), this, SLOT(update_color(int)));
            connect(box,SIGNAL(valueChanged(int)), this, SLOT(update_images()));
            ui->gridLayout->addWidget(box,count+3,j);
            list_of_boxes.emplace_back(box);
        }
        count+=4;
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

void MainWindow::update_images()
{
    QSpinBox* box = qobject_cast<QSpinBox *>(sender());
    int i = box->objectName().split('#').first().toInt();
    int j = box->objectName().split('#').last().toInt();
    QString name = QString::number(i) + "+" + QString::number(j);
    int value = box->value();
    for (QLabel* items : list_of_images)
    {
        if(items->objectName() == name)
        {
            int x = map.value(items).front();
            int y = map.value(items).back();


            QPixmap pix(image_paths.at(value));
            items->setPixmap(pix);
            ui->gridLayout->addWidget(items, x, y);
        }
    }
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
    add_object("destroyable");
}

void MainWindow::on_target_button_clicked()
{
    add_object("target");
}
