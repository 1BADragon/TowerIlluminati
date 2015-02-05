#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>
#include <QPoint>

class Pixel
{
public:
    Pixel(int x, int y);
    Pixel(QPoint p, QColor c);
    void setPoint(int x, int y);
    void setPoint(QPoint p);
    void setColor(int r, int g, int b);
    void setColor(QColor c);
    void applyVector(int x, int y);
    void applyVector(QPoint p);
    QPoint getPoint();
    QColor getColor();
    void operator = (const Pixel& other);
private:
    QPoint point;
    QColor color;
};

#endif // PIXEL_H
