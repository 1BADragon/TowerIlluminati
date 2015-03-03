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
    Frame tempFrame;
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            tempFrame.setFullGridPixelColor(i,j,this->FullGridPixel(i,j)->getColor());
        }
    }
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            if(i + y < FULLGRIDHEIGHT && i + y >= 0)
            {
                if(j + x < FULLGRIDWIDTH && j + x >= 0)
                {
                    this->setFullGridPixelColor(i,j, tempFrame.FullGridPixel(i+y,j+x)->getColor());
                }
                else
                {
                    this->setFullGridPixelColor(i,j,"grey");
                }
            }
            else
            {
                this->setFullGridPixelColor(i,j,"grey");
            }
        }
    }
}

Pixel *Frame::FullGridPixel(int x, int y){
    return fullGrid[x][y];
}
