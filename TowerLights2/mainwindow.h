#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "colorwheel.h"
#include "colorpalette.h"
#include "movie.h"
#include "timer.h"
#include "previewer.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QtDeclarative/QDeclarativeView>
#include <QQmlContext>
#include <QString>
#include <QPalette>
#include <QQuickItem>
#include <QFileDialog>
#include <QTime>
#include <QFileDialog>

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

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_redSpinBox_valueChanged(int arg1);

    void on_blueSpinBox_valueChanged(int arg1);

    void on_greenSpinBox_valueChanged(int arg1);

    void updateColorSpinBoxes(QColor);

    void towerPainting();

    void towerReleased();

    void on_actionOpen_Audio_File_triggered();

    void on_actionOpen_triggered();


    void on_newFrameButton_clicked();

    void on_previewScrollBar_valueChanged(int value);

    void on_actionAfter_triggered();

    void on_currentTime_timeChanged(const QTime &time);

    void on_playPauseButton_clicked();

    void on_stopButton_clicked();

    void on_upButton_clicked();

    void on_randomButton_clicked();

    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_downLeftButton_clicked();

    void on_upLeftButton_clicked();

    void on_upRightButton_clicked();

    void on_downRightButton_clicked();

    void keyPressEvent(QKeyEvent *event);

    void on_actionPreview_Mode_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    Previewer previewer;

    ColorWheel *cWheel;

    QSpinBox *red;
    QSpinBox *blue;
    QSpinBox *green;

    QQuickItem *previewTowers[7][10][4];
    QQuickItem *fullTower[20][12];
    QQuickItem *mainTower[10][4];
    QQuickItem *colorPallet[2][8];

    bool ping;
    bool stop;
    bool towerClicked;

    Movie *currentMovie;
    QMediaPlayer *audio;

    Timer timer;

    void fixPalletBackground();
    void saveCurrentFrame();
    void updateUI();
    void setUpMats();
    void changeCurrentFrame(int value);
    void updateMainTower();
    void upDatePreviewer();

};

#endif // MAINWINDOW_H
