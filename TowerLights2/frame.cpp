#include "frame.h"

Frame::Frame()
{
    *grid = new Pixel[10];
    *fullGrid = new Pixel[20];

    for(int i = 0; i < 20; i++){
        if( i < 10){
            grid[i] = new Pixel[4];
        }
        fullGrid[i] = new Pixel[12];
    }
}
