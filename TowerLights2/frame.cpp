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
            towerGrid[i][j] = fullGrid[i+5][j+4];
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

void Frame::setFullGridPixelColor(int x, int y, QColor c){
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

void Frame::applyVector(int x, int y)
{
    Frame temp;
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            temp.setFullGridPixelColor(i,j,this->FullGridPixel(i,j)->getColor());
        }
    }
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            if((i + y) > 0 && (i + y) < FULLGRIDHEIGHT)
            {
                if((j + x) > 0 && (j + x) < FULLGRIDWIDTH)
                {
                    this->setFullGridPixelColor(i+y,j+x,temp.FullGridPixel(i+y,i+x)->getColor());
                }
                else
                {
                    this->setFullGridPixelColor(i+y,j+x,"grey");
                }
            }
            else
            {
                this->setFullGridPixelColor(i+y,j+x,"grey");
            }
        }
    }
}

Pixel *Frame::FullGridPixel(int x, int y){
    return fullGrid[x][y];
}
