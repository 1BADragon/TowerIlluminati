#include "previewer.h"
#include "ui_previewer.h"

Previewer::Previewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Previewer)
{
    ui->setupUi(this);
    currentMovie = NULL;
    currentAudio = NULL;

    currentFrameNumber = 0;
    ui->horizontalScrollBar->setRange(0,0);

    setUpMatrix();

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
        currentColumn = rows[0]->childItems();
        for(int y = 0; y < 10; y++)
        {
            tower[y][x] = currentColumn[y];
        }
    }

}

void Previewer::updateUI()
{
    Frame* temp = currentMovie->getFrame(currentFrameNumber);
    for(int x = 0; x < 4; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            tower[y][x]->setProperty("color", temp->TowerGridPixel(y,x)->getColor());
        }
    }
    qApp->processEvents();
}
