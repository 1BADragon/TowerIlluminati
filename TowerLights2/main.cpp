/*
 * Tower Animator Project
 */
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
    Q_INIT_RESOURCE(resources);
    MainWindow w;
    w.show();

    return a.exec();
}
