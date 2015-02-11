#ifndef PIXELGROUP_H
#define PIXELGROUP_H
#include <QColor>
#include <QPoint>
#include <QList>
#include "pixel.h"

using namespace std;

class PixelGroup
{
public:
    PixelGroup();
    //PixelGroup moveNew(QPoint vector);
    //PixelGroup moveNew(int x, int y);
    void move(QPoint vector);
    void move(int x, int y);
    int getSize();
    void addPixel(Pixel p);
private:
    QList <Pixel> group;
    void setGroup(QList<Pixel> g);
};

#endif // PIXELGROUP_H
