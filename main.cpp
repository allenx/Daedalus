#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setFixedWidth(640);
    w.setFixedHeight(640);
    w.show();


    return app.exec();
}
