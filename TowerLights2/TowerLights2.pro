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
    grid.cpp \
    pixel.cpp \
    pixelgroup.cpp \
    frame.cpp \
    movie.cpp \
    colorwheel.cpp \
    color.cpp \
    colorpalette.cpp

HEADERS  += mainwindow.h \
    grid.h \
    pixel.h \
    pixelgroup.h \
    frame.h \
    movie.h \
    colorwheel.h \
    color.h \
    colorpalette.h

FORMS    += mainwindow.ui

OTHER_FILES +=

DISTFILES += \
    colorPallet.qml \
    windowScroll.qml \
    currentColor.qml \
    towerGrid.qml

RESOURCES += \
    resources.qrc
