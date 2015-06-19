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


void MainWindow::saveCurrentFrame()
{
    Frame *temp = currentMovie->getFrame(currentMovie->getFrameNumber());
    QColor tempC;



    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            tempC = fullTower[i][j]->property("color").value<QColor>();
            temp->setFullGridPixelColor(i, j, tempC);
        }
    }
}

void MainWindow::updateUI()
{
    //Update Previewer
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            previewTowers[3][i][j]->setProperty("color",
                                                mainTower[i][j]->property("color"));
        }
    }

    //Previous Frames
    int tempVal;
    for(int i = 0; i < 3; i++)
    {
        tempVal = currentMovie->getFrameNumber() - (i+1);
        if(tempVal >= 0)
        {
            for(int j = 0; j < 10; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    previewTowers[2-i][j][k]->
                            setProperty("color",
                                        currentMovie->getFrame(tempVal)->
                                        TowerGridPixel(j,k)->getColor()
                                        );
                }
            }
        }
        else
        {
            for(int j = 0; j < 10; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    previewTowers[2-i][j][k]->
                            setProperty("color","grey");
                }
            }
        }
    }

    //Upcoming Frames
    for(int i = 0; i < 3; i++)
    {
        tempVal = currentMovie->getFrameNumber() + (i+1);
        if(tempVal < currentMovie->getFrameCount())
        {
            for(int j = 0; j < 10; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    previewTowers[4+i][j][k]->
                            setProperty("color",
                                        currentMovie->getFrame(tempVal)->
                                        TowerGridPixel(j,k)->getColor()
                                        );
                }
            }
        }
        else
        {
            for(int j = 0; j < 10; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    previewTowers[4+i][j][k]->
                            setProperty("color","grey");
                }
            }
        }
    }

    //Update Scroll Bar
    ui->previewScrollBar->setRange(0, currentMovie->getFrameCount() - 1);

    //Update Time Box
    QTime tempTime;
    qint64 msecs = currentMovie->getCurrentFrame()->getTimeStamp();

    int hours = msecs/(1000*60*60);
    int minutes = (msecs-(hours*1000*60*60))/(1000*60);
    int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;
    int milliseconds = msecs-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);

    tempTime.setHMS(hours, minutes, seconds, milliseconds);
    ui->currentTime->setTime(tempTime);

    qApp->processEvents();
}

void MainWindow::setUpMats()
{
    QList <QQuickItem *> grid = ui->TowerGridWidget->
            rootObject()->childItems();
    grid = grid[0]->childItems();

    QList <QQuickItem *> allPreview = ui->Previewer->
            rootObject()->childItems();
    QList <QQuickItem *> tempPreview;



    int count = 0;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            fullTower[i][j] = grid[count++];
        }
    }


    for(int x = 0; x < 7; x++){
        count = 0;
        tempPreview = allPreview[0]->childItems()[x]->childItems();
        //std::cout<<tempPreview.length()<<std::endl;
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                previewTowers[x][i][j] = tempPreview[count++];
            }
        }
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            mainTower[i][j] = fullTower[i+5][j+4];
        }
    }

    //Color Pallet

    QList<QQuickItem *> colorP = ui->colorPalletWidget->rootObject()->
            childItems()[0]->childItems();
    count = 0;
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 8; j++)
            colorPallet[i][j] = colorP[count++];

}

//this function sets the background color of the widgest
//to the same color of the mainwindow background color
void MainWindow::fixPalletBackground(){
    QQuickWidget *colorPallet = ui->colorPalletWidget;
    QQuickWidget *towerGrid = ui->TowerGridWidget;
    QQuickWidget *windowScroll = ui->Previewer;

    colorPallet->setClearColor(QColor(240,240,240));
    towerGrid->setClearColor(Qt::white);
    windowScroll->setClearColor(QColor(240,240,240));
}
