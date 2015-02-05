#include "frame.h"

Frame::Frame()
{
    for(int i = 0; i < FULLGRIDWIDTH; i++){
        for(int j = 0; j < FULLGRIDHEIGHT; j++){
            fullGrid[i][j] = new Pixel(i, j);
        }
    }
    for(int i = 0; i < TOWERWIDTH; i++){
        for(int j = 0; j < TOWERHEIGHT; j++){
            towerGrid[i][j] = fullGrid[i+4][j+5];
        }
    }
    timeStamp = 0;
}

Frame::Frame(const Frame &original)
{
    for(int i = 0; i < FULLGRIDWIDTH; i++){
        for(int j = 0; j < FULLGRIDHEIGHT; j++){
            fullGrid[i][j] = new Pixel(original.fullGrid[i][j]->getPoint(), original.fullGrid[i][j]->getColor());
        }
    }
    for(int i = 0; i < TOWERWIDTH; i++){
        for(int j = 0; j < TOWERHEIGHT; j++){
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

void Frame::setPixel(int x, int y, QColor c){
    fullGrid[x][y]->setColor(c);
    fullGrid[x][y]->setPoint(x, y);
}
