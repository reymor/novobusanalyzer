#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QDesktopWidget dw;

    int x = dw.width() * 0.6;
    int y = dw.height() * 0.6;
    // w.setFixedSize(x,y);
    w.resize(x,y);

    w.show();
    return a.exec();
}
