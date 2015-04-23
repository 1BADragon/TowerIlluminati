/*! \mainpage
 * Title: Tower Animator Software Design
 *
 * Team Members:
 *  1st Semester:
 *      -# Matthew Brown
 *      -# Ranger Adams
 *      -# Paul Bailey
 *      -# Emeth Thomson
 *
 *  2nd Semester:
 *      -# Matthew Brown
 *      -# Ranger Adams
 *      -# Cameron Simon
 *
 * This Program was created through the University of Idaho's capstone design class.
 * The use of this program is for the ACM club's tower light show.
 * If you wish to edit the source of this program please do so through the permisison of Dr. Rinker
 *  at the University of Idaho, Moscow.
 *
 */
#include "mainwindow.h"
#include "colorwheel.h"
#include <QApplication>
#include <QColor>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QtDeclarative/QDeclarativeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(resources);
    MainWindow w;
    w.show();

    return a.exec();
}
