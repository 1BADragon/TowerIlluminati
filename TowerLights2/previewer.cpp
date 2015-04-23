#include "previewer.h"
#include "ui_previewer.h"

Previewer::Previewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Previewer)
{
    ui->setupUi(this);
    currentMovie = NULL;
    currentAudio = NULL;

    timer = new Timer();

    currentFrameNumber = 0;
    ui->horizontalScrollBar->setRange(0,0);

    setUpMatrix();

    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            tower[y][x]->setProperty("color", "grey");
        }
    }

    stop = true;

}

Previewer::~Previewer()
{
    delete ui;
}

void Previewer::updateData(Movie *movie, QMediaPlayer *audio)
{
    currentMovie = movie;
    currentAudio = audio;

    ui->horizontalScrollBar->setRange(0, currentMovie->getFrameCount() - 1);
    currentFrameNumber = 0;
}

void Previewer::on_pushButton_clicked()
{
    if(currentMovie != NULL)
    {
        if (stop==false){
            stop = true;
            currentAudio->pause();
            updateUI();
        }else{
            stop = false;
            int maxFrames = currentMovie->getFrameCount();
            Frame* currentFrame = currentMovie->getFrame(currentFrameNumber);
            Frame* nextFrame = currentMovie->getFrame(currentFrameNumber + 1);
            timer->start(currentFrame->getTimeStamp());
            currentAudio->setPosition(currentFrame->getTimeStamp());
            currentAudio->play();
            qint64 time;

            if (nextFrame == NULL)
            {
                stop = true;
            }
            while(stop == false){
                if(currentFrameNumber < maxFrames){
                    if (true){ //this is flag for whether a music file is loaded or not
                        time = timer->getTime();
                    }
                    else{
                        time = currentAudio->position();
                    }
                    if(nextFrame->getTimeStamp() <= time)
                    {
                        currentFrame = nextFrame;
                        nextFrame = currentMovie->getFrame(currentFrameNumber+1);

                        if(nextFrame != NULL && (currentFrameNumber) < maxFrames)
                        {
                            ui->horizontalScrollBar->setValue(currentFrameNumber + 1);
                            updateUI();
                            currentFrameNumber++;
                        }
                        else
                        {
                            stop = true;
                        }
                    }
                }
                else{
                    stop = true;
                }
            }
            timer->stop();
            currentAudio->pause();
        }
    }
}

void Previewer::on_horizontalScrollBar_valueChanged(int value)
{
    currentFrameNumber = value;
    updateUI();
}

void Previewer::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    updateUI();
}

void Previewer::setUpMatrix()
{
    QList <QQuickItem *> rows = ui->quickWidget->
            rootObject()->childItems()[0]->childItems();

    QList <QQuickItem *> currentColumn;

    for(int x = 0; x < 4; x++)
    {
        currentColumn = rows[x]->childItems();
        for(int y = 0; y < 10; y++)
        {
            tower[y][x] = currentColumn[y];
        }
    }

}

void Previewer::updateUI()
{
    if(currentMovie != NULL)
    {
        Frame* temp = currentMovie->getFrame(currentFrameNumber);
        for(int x = 0; x < 4; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                tower[y][x]->setProperty("color", temp->TowerGridPixel(y,x)->getColor());
            }
        }
    }
    else
    {
        qDebug() << "currentMovie is NULL!!";
    }
    qApp->processEvents();
}
