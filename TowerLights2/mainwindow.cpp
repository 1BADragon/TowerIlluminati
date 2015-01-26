#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colorwheel.h"
#include <cstdlib>
#include <QtDeclarative/QDeclarativeView>
#include <QQmlContext>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ColorWheel *cWheel = new ColorWheel(ui->colorWheelWidget);

    cWheel->show();
    cWheel->size();
    ui->colorWheelWidget->show();
    ui->TowerGrid->rootContext()->setContextProperty("currentColor", cWheel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}
