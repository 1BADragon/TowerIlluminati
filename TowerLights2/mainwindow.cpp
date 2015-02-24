#include <QFileDialog>
#include "mainwindow.h"

//Set Global Filename
QString fileName;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{  
  //Initiate the UI
  ui->setupUi(this);

  //Setup media.
  currentMovie = new Movie();

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

  setUpMats();
  updateUI();
}

MainWindow::~MainWindow()
{
  delete ui;
}

//this function is called when file>>exit is selected
void MainWindow::on_actionExit_triggered()
{
  exit(0);
}

//this function is called when file>>export is selected
void MainWindow::on_actionExport_triggered()
{
    saveCurrentFrame();

    //get filename and location for save
    QString exportFileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                "/home/untitled.tan",
                                tr("Images (*.tan)"));
    // Create a new file
    QFile file(exportFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    //Version Number
    out << "0.3\n";

    //Current Color
    out << red->value() << " " << green->value() << " " << blue->value()
        << " 0 0 0 0 0 0\n";

    //Color Pallet RGB values
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < 8; j++)
      {
          QVariant temp = colorPallet[i][j]->property("color");
          QColor tempColor = temp.value<QColor>();
          QString tempRed = QString("%1").arg(tempColor.red());
          QString tempGreen = QString("%1").arg(tempColor.green());
          QString tempBlue = QString("%1").arg(tempColor.blue());
          out << tempRed << " " << tempGreen << " " << tempBlue << " ";
       }
    }
    out << "0 0 0 0 0 0\n";
    out << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
           "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";

    //Frame Count and size
    out << currentMovie->getFrameCount() << " 10 4\n";

    //RGB Values for each pixel of each frame
    int temp = currentMovie->getFrameCount();
    for(int i = 0; i < temp; i++)
    {
        //Get timestamp of frame and convert to correct format for output
        qint64 msecs = currentMovie->getFrame(i)->getTimeStamp();
        int hours = msecs/(1000*60*60);
        int minutes = (msecs-(hours*1000*60*60))/(1000*60);
        int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;
        int milliseconds = msecs-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);
        //pad output with zeroes
        QString tempMin = QString("%1").arg(minutes, 2, 10, QChar('0'));
        QString tempSec = QString("%1").arg(seconds, 2, 10, QChar('0'));
        QString tempMilli = QString("%1").arg(milliseconds, 3, 10, QChar('0'));
        out << tempMin << ":" << tempSec << "." << tempMilli << "\n";

        for(int j = 0; j < 10; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                QColor tempColor = currentMovie->getFrame(i)->TowerGridPixel(j,k)->getColor();
                QString tempRed = QString("%1").arg(tempColor.red());
                QString tempGreen = QString("%1").arg(tempColor.green());
                QString tempBlue = QString("%1").arg(tempColor.blue());
                if(tempRed == "128" && tempGreen == "128" && tempBlue == "128")
                {
                    out << "0 0 0 ";
                }
                else
                {
                    out << tempRed << " " << tempGreen << " " << tempBlue << " ";
                }
                if( k == 3)
                {
                    out << "\n";
                }
            }
        }
    }

    file.close();
}

//this function is called when file>>Save As is selected
void MainWindow::on_actionSave_As_triggered()
{
    saveCurrentFrame();

    //get filename and location for save
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "/home/untitled.tan2",
                                tr("Images (*.tan2)"));
    // Create a new file
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    //Version Number
    out << "0.4\n";

    //Current Color
    out << red->value() << " " << green->value() << " " << blue->value()
        << " 0 0 0 0 0 0\n";

    //Color Pallet RGB values
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < 8; j++)
      {
          QVariant temp = colorPallet[i][j]->property("color");
          QColor tempColor = temp.value<QColor>();
          QString tempRed = QString("%1").arg(tempColor.red());
          QString tempGreen = QString("%1").arg(tempColor.green());
          QString tempBlue = QString("%1").arg(tempColor.blue());
          out << tempRed << " " << tempGreen << " " << tempBlue << " ";
       }
    }
    out << "0 0 0 0 0 0\n";
    out << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
           "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";

    //Frame Count and size
    out << currentMovie->getFrameCount() << " 10 4\n";

    //RGB Values for each pixel of each frame
    int temp = currentMovie->getFrameCount();
    for(int i = 0; i < temp; i++)
    {
        out << currentMovie->getFrame(i)->getTimeStamp() << "\n";
        for(int j = 0; j < 20; j++)
        {
            for(int k = 0; k < 12; k++)
            {
                QColor tempColor = currentMovie->getFrame(i)->FullGridPixel(j,k)->getColor();
                QString tempRed = QString("%1").arg(tempColor.red());
                QString tempGreen = QString("%1").arg(tempColor.green());
                QString tempBlue = QString("%1").arg(tempColor.blue());
                if(tempRed == "128" && tempGreen == "128" && tempBlue == "128")
                {
                    out << "0 0 0 ";
                }
                else
                {
                    out << tempRed << " " << tempGreen << " " << tempBlue << " ";
                }
                if( k == 11)
                {
                    out << "\n";
                }
            }
        }
    }

    file.close();
}

//this function is called when file>>Save is selected
void MainWindow::on_actionSave_triggered()
{
    saveCurrentFrame();

    if(fileName == NULL)
    {
        //get filename and location for save
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                "/home/untitled.tan2",
                                tr("Images (*.tan2)"));
    }
    // Create a new file
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    //Version Number
    out << "0.4\n";

    //Current Color
    out << red->value() << " " << green->value() << " " << blue->value()
        << " 0 0 0 0 0 0\n";

    //Color Pallet RGB values
    for(int i = 0; i < 2; i++)
    {
      for(int j = 0; j < 8; j++)
      {
          QVariant temp = colorPallet[i][j]->property("color");
          QColor tempColor = temp.value<QColor>();
          QString tempRed = QString("%1").arg(tempColor.red());
          QString tempGreen = QString("%1").arg(tempColor.green());
          QString tempBlue = QString("%1").arg(tempColor.blue());
          out << tempRed << " " << tempGreen << " " << tempBlue << " ";
       }
    }
    out << "0 0 0 0 0 0\n";
    out << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
           "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";

    //Frame Count and size
    out << currentMovie->getFrameCount() << " 10 4\n";

    //RGB Values for each pixel of each frame
    int temp = currentMovie->getFrameCount();
    for(int i = 0; i < temp; i++)
    {
        out << currentMovie->getFrame(i)->getTimeStamp() << "\n";
        for(int j = 0; j < 20; j++)
        {
            for(int k = 0; k < 12; k++)
            {
                QColor tempColor = currentMovie->getFrame(i)->FullGridPixel(j,k)->getColor();
                QString tempRed = QString("%1").arg(tempColor.red());
                QString tempGreen = QString("%1").arg(tempColor.green());
                QString tempBlue = QString("%1").arg(tempColor.blue());
                if(tempRed == "128" && tempGreen == "128" && tempBlue == "128")
                {
                    out << "0 0 0 ";
                }
                else
                {
                    out << tempRed << " " << tempGreen << " " << tempBlue << " ";
                }
                if( k == 11)
                {
                    out << "\n";
                }
            }
        }
    }

    file.close();
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
  updateUI();
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

void MainWindow::saveCurrentFrame()
{
  Frame *temp = currentMovie->getFrame(currentMovie->getFrameNumber());
  QColor tempC;



  for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
      for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
          tempC = fullTower[i][j]->property("color").value<QColor>();
          temp->setFullGridPixel(i, j, tempC);
        }
    }
}

void MainWindow::on_actionOpen_Audio_File_triggered()
{
  QFileDialog openAudioDialog(this);
  //openAudioDialog.setVisible(true);
  //if (openAudioDialog.exec())
  //    openAudioDialog.urlSelected(currentMovie->audioFile);
  currentMovie->setAudio(QUrl::fromLocalFile(QFileDialog::getOpenFileName(this,
                                                                          tr("Open Audio"), "/", tr("Audio Files (*.wav *.mp3 *.m4a)"))));
  //std::cout << "File is" << currentMovie->getAudioFile().toString().toStdString() << std::endl;
  //std::cerr << currentMovie->audioFile.toString().toStdString();
  //audioPlayer->setMedia(currentMovie->audioFile);
  //std::cout << audioPlayer->duration();
  //ui->mediaSlider->setRange(0,audioPlayer->duration()/1000);

}

void MainWindow::on_actionOpen_triggered()
{
  QFileDialog openFileDialog(this);
  currentMovie->setFile(QUrl::fromLocalFile(QFileDialog::getOpenFileName(this,
                                                                         tr("Open File"), "/", tr("Tower Light Files (*.tan, *.tan2)"))));

  ui->previewScrollBar->setRange(0, currentMovie->getFrameCount());
}

void MainWindow::on_newFrameButton_clicked()
{
  int frameNumber = currentMovie->getFrameNumber();
  currentMovie->insertFrame(frameNumber+1, new Frame());
  qint64 newTime;

  QTime time = ui->intervalTime->time();

  newTime = time.hour()*(1000*60*60) + time.minute()*(1000*60) + time.second()*1000 + time.msec();

  newTime += currentMovie->getCurrentFrame()->getTimeStamp();

  currentMovie->getFrame(frameNumber+1)->setTimeStamp(newTime);
  updateUI();
}

void MainWindow::on_previewScrollBar_valueChanged(int value)
{
  /*
     * step 1 save current frame
     * step 2 switch to frame "value"
     * step 3 update previewer to reflect frames
     */
  Frame *temp = currentMovie->getFrame(currentMovie->getFrameNumber());
  QColor tempC;



  for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
      for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
          tempC = fullTower[i][j]->property("color").value<QColor>();
          temp->setFullGridPixel(i, j, tempC);
        }
    }

  temp = currentMovie->getFrame(value);
  currentMovie->setFrameNumber(value);


  for(int i = 0; i < FULLGRIDHEIGHT; i++)
    {
      for(int j = 0; j < FULLGRIDWIDTH; j++)
        {
          fullTower[i][j]->setProperty("color",temp->FullGridPixel(i,j)->getColor());
        }
    }

  updateUI();
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

void MainWindow::on_actionAfter_triggered()
{
  on_newFrameButton_clicked();
}

void MainWindow::on_currentTime_timeChanged(const QTime &time)
{
  qint64 tempTime = time.hour()*(1000*60*60) + time.minute()*(1000*60) + time.second()*1000 + time.msec();
  currentMovie->getCurrentFrame()->setTimeStamp(tempTime);
}

void MainWindow::on_playPauseButton_clicked()
{
    saveCurrentFrame();
    stop = false;
    int currentFrameNumber = currentMovie->getFrameNumber();
    int maxFrames = currentMovie->getFrameCount();
    Frame* currentFrame = currentMovie->getCurrentFrame();
    Frame* nextFrame = currentMovie->getNextFrame();
    timer.start(currentFrame->getTimeStamp());

    while(stop == false){
        if(currentFrameNumber < maxFrames){
            qDebug() << "currentFrame: " << currentFrame->getTimeStamp();
            qDebug() << "currentTime: " << timer.getTime();
            if(currentFrame->getTimeStamp() <= timer.getTime()){
                on_previewScrollBar_valueChanged(currentFrameNumber + 1);
                currentFrameNumber++;
                currentFrame = nextFrame;
                currentMovie->setFrameNumber(currentFrameNumber);
                nextFrame = currentMovie->getNextFrame();
            }
        }
        else{
            stop = true;
        }
        qDebug() << currentFrameNumber;
    }
    timer.stop();
}

void MainWindow::on_stopButton_clicked()
{
    stop = true;
}
