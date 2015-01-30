#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{  
  //Initiate the UI
  ui->setupUi(this);

  //Attach Widgets to the UI
  cWheel = new ColorWheel(ui->colorWheelWidget);
  cWheel->show();
  cWheel->size();

  ui->Previewer->setSource(QUrl("qrc:/windowScroll.qml"));
  ui->TowerGridWidget->setSource(QUrl("qrc:/towerGrid.qml"));
  ui->colorPalletWidget->setSource(QUrl("qrc:/colorPallet.qml"));
  ui->currentColorWidget->setSource(QUrl("qrc:/currentColor.qml"));

  //Add these object as context properties in the qml documents
  ui->TowerGridWidget->rootContext()->setContextProperty("currentColor", cWheel);
  ui->colorPalletWidget->rootContext()->setContextProperty("currentColor", cWheel);

  colorPalette *CPA = new colorPalette();
  ui->colorPalletWidget->rootContext()->setContextProperty("paletteColors", CPA);

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

  /*
  QQuickItem *towerGrid = ui->TowerGridWidget->rootObject()->findChild<QQuickItem*>("towerGrid");
  if(towerGrid != NULL)
    connect(towerGrid, SIGNAL(towerClicked()),
            this, SLOT(towerPainting()));
  */

  //set some inital values for variables...
  //this is a constructor after all
  ping = true;

  //Sets the background of the widgets to be the same
  //as the mainWindow background color.
  fixPalletBackground();
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
