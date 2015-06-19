#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{  
    //Initiate the UI
    ui->setupUi(this);

    //Setup media.
    currentMovie = new Movie();
    audio = new QMediaPlayer;

    //Attach Widgets to the UI
    cWheel = new ColorWheel(ui->colorWheelWidget);
    cWheel->show();
    cWheel->size();

    //Add these object as context properties in the qml documents
    ui->TowerGridWidget->rootContext()->setContextProperty("currentColor", cWheel);
    ui->colorPalletWidget->rootContext()->setContextProperty("currentColor", cWheel);

    colorPalette *CPA = new colorPalette();
    ui->colorPalletWidget->rootContext()->setContextProperty("paletteColors", CPA);

    ui->Previewer->setSource(QUrl("qrc:/windowScroll.qml"));
    ui->TowerGridWidget->setSource(QUrl("qrc:/towerGrid.qml"));
    ui->colorPalletWidget->setSource(QUrl("qrc:/colorPallet.qml"));
    ui->currentColorWidget->setSource(QUrl("qrc:/currentColor.qml"));



    //create initial values for the color selectors
    red = ui->redSpinBox;
    blue = ui->blueSpinBox;
    green = ui->greenSpinBox;

    red->setValue(cWheel->color().red());
    blue->setValue(cWheel->color().blue());
    green->setValue(cWheel->color().green());

    QQuickItem *currentColor = ui->currentColorWidget->rootObject();
    currentColor->setProperty("color", cWheel->color().name());

    //This connects the Signal "colorChange" to the function
    //"updateSpinBoxes so that when the signal is emited the
    //function is called
    connect(cWheel, SIGNAL(colorChange(QColor)),
            this, SLOT(updateColorSpinBoxes(QColor)));


    QQuickItem *towerGrid = ui->TowerGridWidget->rootObject();
    if(towerGrid != NULL)
        connect(towerGrid, SIGNAL(towerClicked()),
                this, SLOT(towerPainting()));

    //set some inital values for variables...
    //this is a constructor after all
    ping = true;

    //Sets the background of the widgets to be the same
    //as the mainWindow background color.
    fixPalletBackground();

    //create intial frame
    currentMovie->insertFrame(0, new Frame());

    QTime tempTime(0,0,0,50);
    ui->intervalTime->setMinimumTime(tempTime);
    setUpMats();
    updateUI();

    connect(audio, SIGNAL(durationChanged(qint64)),this,SLOT(on_audioDurationChanged(qint64)));
    ui->mediaSlider->setRange(0,0);

    //set up some button filters so they can capture shift presses
    ui->newFrameButton->installEventFilter(this);

    //set up previewer window
    previewer.hide();

    //program has not been edited on first open
    edited = false;

    saveTimer = new QTimer();
    connect(saveTimer, SIGNAL(timeout()), this, SLOT(saveWarning()));
    saveTimer->setInterval(600000); //auto save every 10 min
    saveTimer->start();

    stop = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//these functions sync the spin boxes and the colorwheel
void MainWindow::on_redSpinBox_valueChanged(int arg1){
    QColor temp = cWheel->color();
    temp.setRed(arg1);
    if(ping)
        cWheel->updateColor(temp);
    ping = true;
}

void MainWindow::on_blueSpinBox_valueChanged(int arg1)
{
    QColor temp = cWheel->color();
    temp.setBlue(arg1);
    if(ping)
        cWheel->updateColor(temp);
    ping = true;
}

void MainWindow::on_greenSpinBox_valueChanged(int arg1)
{
    QColor temp = cWheel->color();
    temp.setGreen(arg1);
    if(ping)
        cWheel->updateColor(temp);
    ping = true;
}

//this is the function that is called when the signal
//"colorChange" is emited
void MainWindow::updateColorSpinBoxes(QColor newColor){
    QQuickItem *currentColor = ui->currentColorWidget->rootObject();
    currentColor->setProperty("color", newColor.name());

    if(ping == false){
        red->setValue(newColor.red());
        green->setValue(newColor.green());
        blue->setValue(newColor.blue());
        ping = false;
    }else {
        ping = false;
    }
}

void MainWindow::towerPainting()
{
    edited = true;
    updateUI();
}

void MainWindow::on_actionOpen_Audio_File_triggered()
{
    QUrl fileToOpen = QUrl::fromLocalFile(QFileDialog::getOpenFileName(this,
                                                                       tr("Open Audio"), "/", tr("Audio Files (*.wav *.mp3 *.m4a)")));
    if (!fileToOpen.isEmpty()){
        currentMovie->setAudio(fileToOpen);
        audio->setMedia(currentMovie->getAudioFile());
        audio->stop();
    }
}

void MainWindow::on_previewScrollBar_valueChanged(int value)
{
    changeCurrentFrame(value);
    ui->mediaSlider->setValue(value);
}

void MainWindow::changeCurrentFrame(int value)
{
    /*
       * step 1 save current frame
       * step 2 switch to frame "value"
       * step 3 update previewer to reflect frames
       */
    Frame *tempFrame = currentMovie->getFrame(currentMovie->getFrameNumber());
    QColor tempC;



    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            tempC = fullTower[i][j]->property("color").value<QColor>();
            tempFrame->setFullGridPixelColor(i, j, tempC);
        }
    }

    tempFrame = currentMovie->getFrame(value);
    currentMovie->setFrameNumber(value);


    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            fullTower[i][j]->setProperty("color",tempFrame->FullGridPixel(i,j)->getColor());
        }
    }

    updateUI();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(edited)
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              on_actionSave_triggered();
              qApp->quit();
              break;
          case QMessageBox::Discard:
              qApp->quit();
              break;
          case QMessageBox::Cancel:
              event->ignore();
              break;
          default:
              // should never be reached
              break;
        }
    }
    else
    {
        qApp->quit();
    }
}

void MainWindow::on_actionAfter_triggered()
{
    on_newFrameButton_clicked();
}

void MainWindow::on_currentTime_timeChanged(const QTime &time)
{
    qint64 tempTime = time.hour()*(1000*60*60) + time.minute()*(1000*60) + time.second()*1000 + time.msec();
    currentMovie->getCurrentFrame()->setTimeStamp(tempTime);
    if(stop == true)
    {
        saveCurrentFrame();
        currentMovie->sortFrames();
        updateMainTower();
        updateUI();
    }
}

void MainWindow::on_playPauseButton_clicked()
{
    if (stop==false){
        stop = true;
        audio->pause();
        updateUI();
    }else{
        saveCurrentFrame();
        stop = false;
        int currentFrameNumber = currentMovie->getFrameNumber();
        int maxFrames = currentMovie->getFrameCount();
        Frame* currentFrame = currentMovie->getCurrentFrame();
        Frame* nextFrame = currentMovie->getNextFrame();
        timer.start(currentFrame->getTimeStamp());
        audio->setPosition(currentFrame->getTimeStamp());
        audio->play();
        qint64 time;

        if (nextFrame == NULL)
        {
            stop = true;
        }
        while(stop == false){
            if(currentFrameNumber < maxFrames){
                //qDebug() << "currentFrame: " << currentFrame->getTimeStamp();
                //qDebug() << "currentTime: " << timer.getTime();
                //qDebug() << "currentFrame: " << currentFrame;
                //qDebug() << "currentFrameNumber: " << currentFrameNumber;
                //qDebug() << "maxFrames: " << maxFrames;
                //qDebug() << "";
                if (true){ //this is flag for whether a music file is loaded or not
                    time = timer.getTime();
                }
                else{
                    time = audio->position();
                }
                if(nextFrame->getTimeStamp() <= time)
                {
                    changeCurrentFrame(currentFrameNumber);
                    currentFrame = nextFrame;
                    ui->mediaSlider->setSliderPosition(time/1000);

                    if((currentFrameNumber + 1) < maxFrames)
                    {
                        currentMovie->setFrameNumber(currentFrameNumber);
                        nextFrame = currentMovie->getFrame(currentFrameNumber+1);
                        currentFrameNumber += 1;
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
            updateUI();
        }
        timer.stop();
        audio->pause();
    }
    ui->previewScrollBar->setValue(currentMovie->getFrameNumber());
}

void MainWindow::on_stopButton_clicked()
{
    stop = true;
    audio->stop();
    ui->previewScrollBar->setValue(0);
    ui->mediaSlider->setValue(0);
}

void MainWindow::on_randomButton_clicked()
{
    QColor tempColor;
    srand(time(NULL));
    for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
        for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
            tempColor.setRgb(rand()%255, rand()%255, rand()%255);
            fullTower[i][j]->setProperty("color", tempColor);
        }
    }
    saveCurrentFrame();
    updateUI();
}

void MainWindow::on_newFrameButton_clicked()
{
    saveCurrentFrame();
    int frameNumber = currentMovie->getFrameNumber();

    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
        currentMovie->insertFrame(frameNumber+1, new Frame());
    }
    else
    {
        Frame *newFrame = new Frame();
        Frame *oldFrame = currentMovie->getFrame(frameNumber);
        for(int i = 0; i < FULLGRIDHEIGHT; i++)
        {
            for(int j = 0; j < FULLGRIDWIDTH; j++)
            {
                newFrame->setFullGridPixelColor(i,j,oldFrame->FullGridPixel(i,j)->getColor());

                //std::cout << newFrame->FullGridPixel(i,j)->getColor().value() << " ";
            }
            //std::cout << std::endl;
        }
        currentMovie->insertFrame(frameNumber+1, newFrame);
    }

    qint64 newTime;

    QTime time = ui->intervalTime->time();

    newTime = time.hour()*(1000*60*60) + time.minute()*(1000*60) + time.second()*1000 + time.msec();

    newTime += currentMovie->getCurrentFrame()->getTimeStamp();
    audio->setPosition(newTime);

    currentMovie->getFrame(frameNumber+1)->setTimeStamp(newTime);
    ui->previewScrollBar->setRange(0,currentMovie->getFrameCount());
    ui->previewScrollBar->setValue(frameNumber+1);



    updateUI();
}
