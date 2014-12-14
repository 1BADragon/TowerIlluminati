#ifndef ANIMATION_H
#define ANIMATION_H
#include <QPoint>
#include <QMap>

#include "pixelgroup.h"
using namespace std;

class Animation
{
public:
    Animation();
    void addFrame(int x, int y, int sourceTimeStamp, int destTimeStamp);
    void addFrame(QPoint p, int sourceTimeStamp, int destTimeStamp);
    void moveFrame(int x, int y, int timeStamp);
    void moveFrame(QPoint p, int timeStamp);
private:
    QMap <int,PixelGroup> animation;
};

#endif // ANIMATION_H
