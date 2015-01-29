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

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerLights2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    animation.cpp \
    grid.cpp \
    pixel.cpp \
    pixelgroup.cpp \
    frame.cpp \
    movie.cpp \
    colorwheel.cpp \
    color.cpp \
    colorpaletteassigner.cpp

HEADERS  += mainwindow.h \
    animation.h \
    grid.h \
    pixel.h \
    pixelgroup.h \
    frame.h \
    movie.h \
    colorwheel.h \
    color.h \
    colorpaletteassigner.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    TowerGrid.qml

DISTFILES += \
    colorPallet.qml \
    windowScroll.qml

RESOURCES += \
    resources.qrc
