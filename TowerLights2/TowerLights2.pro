#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T15:03:29
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets
QT       += quickwidgets
QT       += qml
QT       += declarative
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerLights2
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    pixel.cpp \
    frame.cpp \
    movie.cpp \
    colorwheel.cpp \
    colorpalette.cpp \
    timer.cpp \
    previewer.cpp \
    mainwindow_util.cpp \
    mainwindow_animationControls.cpp \
    mainwindow_fileio.cpp

HEADERS  += mainwindow.h \
    pixel.h \
    frame.h \
    movie.h \
    colorwheel.h \
    colorpalette.h \
    timer.h \
    previewer.h

FORMS    += mainwindow.ui \
    previewer.ui

OTHER_FILES +=

DISTFILES += \
    colorPallet.qml \
    windowScroll.qml \
    currentColor.qml \
    previewer.qml \
    towerGrid.qml

RESOURCES += \
    resources.qrc
