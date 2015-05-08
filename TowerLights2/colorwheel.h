/*! \file colorwheel.h
 * \brief This file defines the ColorWheel class.
 */

/*! \file colorwheel.h
 * colorwheel.h and colorwheel.cpp are adapted from a github repository
 * accesible at https://github.com/liuyanghejerry/Qt-Plus/tree/master/develop/ColorWheel
 *
 * The author username is liuyanghejerry and he has given a
 * universal concent to "use it in any purpose." This is locatable at:
 * http://qt-project.org/forums/viewthread/19757
 *
 */

#ifndef COLORWHEEL_H
#define COLORWHEEL_H

#include <QWidget>
#include <QString>

/*!
 * \brief The ColorWheel class
 */

class ColorWheel : public QWidget
{
    Q_OBJECT
 public:
    explicit ColorWheel(QWidget *parent = 0);

    virtual QSize sizeHint () const;
    virtual QSize minimumSizeHint () const;

    QColor color();
    Q_INVOKABLE QString colorToString();
    
 signals:
    void colorChange(const QColor &color);
    
    public slots:
        void setColor(const QColor &color);
        void updateColor(const QColor &color);

 protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *);
        void resizeEvent(QResizeEvent *event);
        void paintEvent(QPaintEvent *);
 private:
        QSize initSize;
        QImage wheelImage;
        QImage squareImage;
        QPixmap wheel;
        bool mouseDown;
        QPoint lastPos;
        int margin;
        int wheelWidth;
        QRegion wheelRegion;
        QRegion squareRegion;
        QColor current;
        bool inWheel;
        bool inSquare;
        QColor posColor(const QPoint &point);
        void drawWheelImage(const QSize &newSize);
        void drawIndicator(const int &hue);
        void drawPicker(const QColor &color);
        void drawSquareImage(const int &hue);
        void composeWheel();

private slots:
            void hueChanged(const int &hue);
            void svChanged(const QColor &newcolor);
};

#endif // COLORWHEEL_H
