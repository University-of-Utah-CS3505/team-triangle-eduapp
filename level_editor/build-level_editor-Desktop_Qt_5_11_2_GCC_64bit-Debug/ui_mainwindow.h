/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionload;
    QAction *actionsave;
    QAction *actionnew;
    QWidget *centralWidget;
    QPushButton *spinButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QScrollArea *scrollArea_resources;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *add_resource;
    QPushButton *remove_resource;
    QSpinBox *spin_select_ressource;
    QLabel *label;
    QLabel *resource_label;
    QScrollArea *scrollArea_objects;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *object_label_area;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *object_loc_1_area;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *object_loc_2_area;
    QPushButton *tank_button;
    QPushButton *tree_button;
    QPushButton *target_button;
    QPushButton *remove_object_button;
    QSpinBox *remove_object_box;
    QLabel *label_remove;
    QLabel *label_remove_dynamic;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(962, 753);
        actionload = new QAction(MainWindow);
        actionload->setObjectName(QStringLiteral("actionload"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QStringLiteral("actionsave"));
        actionnew = new QAction(MainWindow);
        actionnew->setObjectName(QStringLiteral("actionnew"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        spinButton = new QPushButton(centralWidget);
        spinButton->setObjectName(QStringLiteral("spinButton"));
        spinButton->setGeometry(QRect(40, 310, 89, 25));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(30, 20, 401, 281));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 385, 265));
        gridLayoutWidget = new QWidget(scrollAreaWidgetContents);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 9, 381, 261));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(130, 310, 48, 26));
        spinBox->setValue(5);
        scrollArea_resources = new QScrollArea(centralWidget);
        scrollArea_resources->setObjectName(QStringLiteral("scrollArea_resources"));
        scrollArea_resources->setGeometry(QRect(430, 20, 471, 381));
        scrollArea_resources->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 469, 379));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents_2);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 451, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        add_resource = new QPushButton(scrollAreaWidgetContents_2);
        add_resource->setObjectName(QStringLiteral("add_resource"));
        add_resource->setGeometry(QRect(10, 290, 121, 25));
        remove_resource = new QPushButton(scrollAreaWidgetContents_2);
        remove_resource->setObjectName(QStringLiteral("remove_resource"));
        remove_resource->setGeometry(QRect(140, 290, 131, 25));
        spin_select_ressource = new QSpinBox(scrollAreaWidgetContents_2);
        spin_select_ressource->setObjectName(QStringLiteral("spin_select_ressource"));
        spin_select_ressource->setGeometry(QRect(290, 290, 48, 26));
        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 320, 141, 17));
        resource_label = new QLabel(scrollAreaWidgetContents_2);
        resource_label->setObjectName(QStringLiteral("resource_label"));
        resource_label->setGeometry(QRect(10, 340, 451, 20));
        scrollArea_resources->setWidget(scrollAreaWidgetContents_2);
        scrollArea_objects = new QScrollArea(centralWidget);
        scrollArea_objects->setObjectName(QStringLiteral("scrollArea_objects"));
        scrollArea_objects->setGeometry(QRect(29, 349, 401, 341));
        scrollArea_objects->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 399, 339));
        verticalLayoutWidget_2 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 10, 111, 321));
        object_label_area = new QVBoxLayout(verticalLayoutWidget_2);
        object_label_area->setSpacing(6);
        object_label_area->setContentsMargins(11, 11, 11, 11);
        object_label_area->setObjectName(QStringLiteral("object_label_area"));
        object_label_area->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(129, 9, 121, 321));
        object_loc_1_area = new QVBoxLayout(verticalLayoutWidget_3);
        object_loc_1_area->setSpacing(6);
        object_loc_1_area->setContentsMargins(11, 11, 11, 11);
        object_loc_1_area->setObjectName(QStringLiteral("object_loc_1_area"));
        object_loc_1_area->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_4 = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(259, 10, 131, 321));
        object_loc_2_area = new QVBoxLayout(verticalLayoutWidget_4);
        object_loc_2_area->setSpacing(6);
        object_loc_2_area->setContentsMargins(11, 11, 11, 11);
        object_loc_2_area->setObjectName(QStringLiteral("object_loc_2_area"));
        object_loc_2_area->setContentsMargins(0, 0, 0, 0);
        scrollArea_objects->setWidget(scrollAreaWidgetContents_3);
        tank_button = new QPushButton(centralWidget);
        tank_button->setObjectName(QStringLiteral("tank_button"));
        tank_button->setGeometry(QRect(440, 440, 141, 25));
        tree_button = new QPushButton(centralWidget);
        tree_button->setObjectName(QStringLiteral("tree_button"));
        tree_button->setGeometry(QRect(440, 470, 141, 25));
        target_button = new QPushButton(centralWidget);
        target_button->setObjectName(QStringLiteral("target_button"));
        target_button->setGeometry(QRect(440, 500, 141, 25));
        remove_object_button = new QPushButton(centralWidget);
        remove_object_button->setObjectName(QStringLiteral("remove_object_button"));
        remove_object_button->setGeometry(QRect(440, 550, 141, 25));
        remove_object_box = new QSpinBox(centralWidget);
        remove_object_box->setObjectName(QStringLiteral("remove_object_box"));
        remove_object_box->setGeometry(QRect(590, 550, 48, 26));
        label_remove = new QLabel(centralWidget);
        label_remove->setObjectName(QStringLiteral("label_remove"));
        label_remove->setGeometry(QRect(440, 580, 191, 17));
        label_remove_dynamic = new QLabel(centralWidget);
        label_remove_dynamic->setObjectName(QStringLiteral("label_remove_dynamic"));
        label_remove_dynamic->setGeometry(QRect(440, 600, 141, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 962, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionload);
        menuFile->addAction(actionsave);
        menuFile->addAction(actionnew);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionload->setText(QApplication::translate("MainWindow", "load", nullptr));
        actionsave->setText(QApplication::translate("MainWindow", "save", nullptr));
        actionnew->setText(QApplication::translate("MainWindow", "new", nullptr));
        spinButton->setText(QApplication::translate("MainWindow", "Add Spin Box", nullptr));
        add_resource->setText(QApplication::translate("MainWindow", "Add Resource", nullptr));
        remove_resource->setText(QApplication::translate("MainWindow", "Remove Resource", nullptr));
        label->setText(QApplication::translate("MainWindow", "Resource to remove:", nullptr));
        resource_label->setText(QApplication::translate("MainWindow", "<AS OF NOW RESOURCES IS UNITERACTABLE!>", nullptr));
        tank_button->setText(QApplication::translate("MainWindow", "Add Tank Spawn", nullptr));
        tree_button->setText(QApplication::translate("MainWindow", "Add Solid (tree)", nullptr));
        target_button->setText(QApplication::translate("MainWindow", "Add Target(box)", nullptr));
        remove_object_button->setText(QApplication::translate("MainWindow", "Remove Object", nullptr));
        label_remove->setText(QApplication::translate("MainWindow", "Object to Remove", nullptr));
        label_remove_dynamic->setText(QApplication::translate("MainWindow", "<PLACEHOLDER>", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
