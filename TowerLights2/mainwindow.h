#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "colorwheel.h"
#include "colorpalette.h"
#include <cstdlib>
#include <iostream>
#include <QtDeclarative/QDeclarativeView>
#include <QQmlContext>
#include <QString>
#include <QPalette>
#include <QQuickItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_redSpinBox_valueChanged(int arg1);

    void on_blueSpinBox_valueChanged(int arg1);

    void on_greenSpinBox_valueChanged(int arg1);

    void updateColorSpinBoxes(QColor);

    void towerPainting();

private:
    Ui::MainWindow *ui;
    ColorWheel *cWheel;
    QSpinBox *red;
    QSpinBox *blue;
    QSpinBox *green;
    bool ping;

    void fixPalletBackground();

};

#endif // MAINWINDOW_H
