#include "frame.h"

Frame::Frame()
{
    for(int i = 0; i < FULLGRIDHEIGHT; i++){
        for(int j = 0; j < FULLGRIDWIDTH; j++){
            fullGrid[i][j] = new Pixel();
        }
    }
    for(int i = 0; i < TOWERHEIGHT; i++){
        for(int j = 0; j < TOWERWIDTH; j++){
            towerGrid[i][j] = fullGrid[i+4][j+5];
        }
    }
    timeStamp = 0;
}

Frame::Frame(const Frame &original)
{
    for(int i = 0; i < FULLGRIDHEIGHT; i++){
        for(int j = 0; j < FULLGRIDWIDTH; j++){
            fullGrid[i][j] = new Pixel(original.fullGrid[i][j]->getColor());
        }
    }
    for(int i = 0; i < TOWERHEIGHT; i++){
        for(int j = 0; j < TOWERWIDTH; j++){
            towerGrid[i][j] = fullGrid[i+4][j+5];
        }
    }
    timeStamp = original.timeStamp;
}

void Frame::setTimeStamp(qint64 time){
    timeStamp = time;
}

qint64 Frame::getTimeStamp(){
    return timeStamp;
}

void Frame::setFullGridPixel(int x, int y, QColor c){
    fullGrid[x][y]->setColor(c);
}

void Frame::setTowerGridPixel(int x, int y, QColor c)
{
    towerGrid[x][y]->setColor(c);
}

Pixel *Frame::TowerGridPixel(int x, int y)
{
    return towerGrid[x][y];
}

Pixel *Frame::FullGridPixel(int x, int y){
    return fullGrid[x][y];
}
