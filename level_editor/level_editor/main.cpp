#include "mainwindow.h"
#include <QApplication>
#include "model.h"

int main(int argc, char *argv[])
{
    model m(0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
