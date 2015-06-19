#include "mainwindow.h"


void MainWindow::updateMainTower()
{
    //Update Main Grid
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            fullTower[i][j]->setProperty("color",
                                         currentMovie->getCurrentFrame()->
                                         FullGridPixel(i,j)->getColor());
        }
    }
}


