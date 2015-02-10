#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>
#include <QPoint>

class Pixel
{
public:
    Pixel();
    Pixel(QColor c);
    void setColor(int r, int g, int b);
    void setColor(QColor c);
    QColor getColor();
    void operator = (const Pixel& other);
private:
    QColor color;
};

#endif // PIXEL_H
