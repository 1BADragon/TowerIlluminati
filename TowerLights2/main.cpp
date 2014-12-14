#include "mainwindow.h"
#include "colorwheel.h"
#include "color.h"
#include <QApplication>
#include <QColor>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QtDeclarative/QDeclarativeView>

extern QWidget widget;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
