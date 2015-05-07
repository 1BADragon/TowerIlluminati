/*! \file mainwindow.h
 *
 * This file defines the mainWindow class of the program
 *
 */
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
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}
/*!
 * \brief The MainWindow class
 */
/*!
 * The MainWindow class defines the GUI of the program.
 * Its used to connect the buttons to the the C++ functions.
 * QT uses its own handles for things like drawing the GUI
 * and processing events so all that the programmer has to
 * do is define high level behavior. This class inherrites
 * the QMainWindow class that is defined by QT. There are
 * these new kind of member functions called slot functions.
 * These functions are connected to parts of the GUI and are
 * predefined in the QT framework when the interface object is created.
 * The name of the function is required and cannot be changed without
 * effecting the behavior of the program. This class also hold data
 * such as matrics that are design to make addressing the on screen
 * tower's easier. The class holds other members that will be
 * defined later on.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //!This function is called when file->exit is triggered
    void on_actionExit_triggered();
    //!This funciton is called when file->new is triggered
    void on_actionNew_triggered();
    //!This funciton is called when file->Export is triggered
    void on_actionExport_triggered();
    //!This funciton is called when file->SaveAs is triggered
    void on_actionSave_As_triggered();
    //!This funciton is called when file->Save is triggered
    void on_actionSave_triggered();
    //!This funciton is called when the red color value is changed
    void on_redSpinBox_valueChanged(int arg1);
    //!This funciton is called when the blue color value is changed
    void on_blueSpinBox_valueChanged(int arg1);
    //!This funciton is called when the green color value is changed
    void on_greenSpinBox_valueChanged(int arg1);
    //!This funciton is called when the color changed signal in the color wheel class is triggered
    void updateColorSpinBoxes(QColor);
    //!This funciton is called when the user changes the tower colors
    void towerPainting();
    //!This funciton is called when file-> Open Audio File is triggered
    void on_actionOpen_Audio_File_triggered();
    //!This funciton is called when file->Open is triggered
    void on_actionOpen_triggered();
    //!This funciton is called when the newFrame button is triggered
    void on_newFrameButton_clicked();
    //!This funciton is called when Scroll bar changes values
    void on_previewScrollBar_valueChanged(int value);
    //!This funciton is called when edit->insert->after is triggered
    void on_actionAfter_triggered();
    //!This funciton is called when the current time value is changed
    void on_currentTime_timeChanged(const QTime &time);
    //!This funciton is called when the play/pause button is clicked
    void on_playPauseButton_clicked();
    //!This funciton is called when the stop button is clicked
    void on_stopButton_clicked();
    //!This funciton is called when the up arrow button is clicked
    void on_upButton_clicked();
    //!This funciton is called when the random button is clicked
    void on_randomButton_clicked();
    //!This funciton is called when the down arrow button is clicked
    void on_downButton_clicked();
    //!This funciton is called when the left arrow button is clicked
    void on_leftButton_clicked();
    //!This funciton is called when the right arrow button is clicked
    void on_rightButton_clicked();
    //!This funciton is called when the down left arrow button is clicked
    void on_downLeftButton_clicked();
    //!This funciton is called when the up left arrow button is clicked
    void on_upLeftButton_clicked();
    //!This funciton is called when the up right arrow button is clicked
    void on_upRightButton_clicked();
    //!This funciton is called when the down right arrow button is clicked
    void on_downRightButton_clicked();
    /*! This funciton is called when any keyboard button is pressed. A switch
     * statement is used to filter exactly which button was pressed.
     */
    void keyPressEvent(QKeyEvent *event);
    //!This funciton is called when playback->previewmode is clicked
    void on_actionPreview_Mode_triggered();
    //!This funciton is called when file->close is triggered
    void on_actionClose_triggered();
    /*! This function is called when a timer runs out. This timer
     * controls the autosave feature of the program.
     */
    void saveWarning();
    //!This funciton is called when the media slider is moved
    void on_mediaSlider_sliderMoved(int position);
    //!This funciton is called when the audio's length changes like when the file changes
    void on_audioDurationChanged(qint64 duration);
    //!This funciton is called when the sort button is clicked
    void on_SortButton_clicked();

private:
    //! The ui is used to interface with the xml generated GUI
    Ui::MainWindow *ui;

    //! This is the previewer window
    Previewer previewer;

    //! This is the colorwheel object
    ColorWheel *cWheel;

    //! This is a spinbox that holds the red value of the current color
    QSpinBox *red;
    //! This is a spinbox that holds the blue value of the current color
    QSpinBox *blue;
    //! This is a spinbox that holds the green value of the current color
    QSpinBox *green;

    //! This matirx points to the quick items that make up the preview section
    QQuickItem *previewTowers[7][10][4];
    //! This matrix points to the quick items that make up the full tower area
    QQuickItem *fullTower[20][12];
    //! This matrix points to the quick items that make up the main tower area
    QQuickItem *mainTower[10][4];
    //! This matrix points to the quick items that make up the color pallet
    QQuickItem *colorPallet[2][8];

    //! This boolean is used to control the coordination of the color selectors
    bool ping;
    //! This boolean is used to control whether the GUI is in playback mode or not
    bool stop;
    //! This boolean signifies whether or not the tower has been edited since last save
    bool edited;

    //! This is the main move object used to contain the frame sequence data
    Movie *currentMovie;
    /*!
     *  audio is used to load and contain the music of the program. This class is a little
     * tricky to use but documentation can be found at http://doc.qt.io/qt-5/qmediaplayer.html
     */
    QMediaPlayer *audio;

    //! This timer is used to control the frame sequence timing when no audio is present
    Timer timer;

    //! This timer is used to control when the program should auto save next
    QTimer *saveTimer;

    //! helper function used to give the color pallet the correct background
    void fixPalletBackground();
    //! helper function used to save the current tower's data to a frame
    void saveCurrentFrame();
    //! helper function used to update the UI based on new data/signals
    void updateUI();
    //! helper function used to set up the QQuickItem matrics
    void setUpMats();
    //! helper function called when the scroll bar changes value.
    void changeCurrentFrame(int value);
    //! helper function used to update the graphical tower to the data stored
    void updateMainTower();

    //! Contains the fileName of the current movie
    QString fileName;

    //! Called when the x is clicked on the main window
    void closeEvent (QCloseEvent *event);

};

#endif // MAINWINDOW_H
