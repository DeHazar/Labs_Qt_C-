#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp1251"));

    return a.exec();
}
