#include "mainwindow.h"

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

  //set up for a new project
  ui->previewScrollBar->setRange(0, currentMovie->getFrameCount());

  setUpMats();
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
    ui->previewScrollBar->setRange(0, currentMovie->getFrameCount());
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

    //Update previewer
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            previewTower[i][j]->setProperty("color",
                mainTower[i][j]->property("color"));
        }
    }
}

void MainWindow::setUpMats()
{
    QList <QQuickItem *> grid = ui->TowerGridWidget->
            rootObject()->childItems();
    grid = grid[0]->childItems();

    QList <QQuickItem *> preview = ui->Previewer->
            rootObject()->childItems();
    preview = preview[0]->childItems()[3]->childItems();



    int count = 0;
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            fullTower[i][j] = grid[count++];
        }
    }

    count = 0;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            previewTower[i][j] = preview[count++];
        }
    }

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            mainTower[i][j] = fullTower[i+5][j+4];
        }
    }

}
