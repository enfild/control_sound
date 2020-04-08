#include "mainwindow_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_Server w;
    w.show();

    return a.exec();
}
