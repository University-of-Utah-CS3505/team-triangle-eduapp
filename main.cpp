#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    auto app = QApplication{argc, argv};
    auto window = MainWindow{};
    window.show();

    return app.exec();
}
