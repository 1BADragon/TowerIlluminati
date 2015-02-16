#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "colorwheel.h"
#include "colorpalette.h"
#include "movie.h"
#include <cstdlib>
#include <iostream>
#include <QtDeclarative/QDeclarativeView>
#include <QQmlContext>
#include <QString>
#include <QPalette>
#include <QQuickItem>
#include <QFileDialog>
#include <QTime>

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

    void on_actionExport_triggered();

    void on_redSpinBox_valueChanged(int arg1);

    void on_blueSpinBox_valueChanged(int arg1);

    void on_greenSpinBox_valueChanged(int arg1);

    void updateColorSpinBoxes(QColor);

    void towerPainting();

    void on_actionOpen_Audio_File_triggered();

    void on_actionOpen_triggered();


    void on_newFrameButton_clicked();

    void on_previewScrollBar_valueChanged(int value);

    void on_actionAfter_triggered();

    void on_currentTime_timeChanged(const QTime &time);

private:
    Ui::MainWindow *ui;

    ColorWheel *cWheel;

    QSpinBox *red;
    QSpinBox *blue;
    QSpinBox *green;

    QQuickItem *previewTowers[7][10][4];
    QQuickItem *fullTower[20][12];
    QQuickItem *mainTower[10][4];

    bool ping;

    Frame *currentFrame;
    Movie *currentMovie;

    void fixPalletBackground();
    void updateUI();
    void setUpMats();

};

#endif // MAINWINDOW_H
