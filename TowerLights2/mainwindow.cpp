#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{  
    ui->setupUi(this);
    cWheel = new ColorWheel(ui->colorWheelWidget);

    cWheel->show();
    cWheel->size();

    ui->Previewer->setSource(QUrl("qrc:/windowScroll.qml"));
    ui->TowerGridWidget->setSource(QUrl("qrc:/TowerGrid.qml"));
    ui->colorPalletWidget->setSource(QUrl("qrc:/colorPallet.qml"));

    ui->colorWheelWidget->show();
    ui->TowerGridWidget->rootContext()->setContextProperty("currentColor", cWheel);


    colorPaletteAssigner *CPA = new colorPaletteAssigner();

    ui->colorPalletWidget->rootContext()->setContextProperty("defaultColor", CPA);

    red = ui->redSpinBox;
    blue = ui->blueSpinBox;
    green = ui->greenSpinBox;

    red->setValue(cWheel->color().red());
    blue->setValue(cWheel->color().blue());
    green->setValue(cWheel->color().green());

    connect(cWheel, SIGNAL(colorChange(QColor)),
            this, SLOT(updateColorSpinBoxes(QColor)));

    ping = true;

    fixPalletBackground();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

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

void MainWindow::updateColorSpinBoxes(QColor newColor){
    red->setValue(newColor.red());
    green->setValue(newColor.green());
    blue->setValue(newColor.blue());
    ping = false;
}

void MainWindow::fixPalletBackground(){
  QQuickWidget *colorPallet = ui->colorPalletWidget;
  QQuickWidget *towerGrid = ui->TowerGridWidget;
  QQuickWidget *windowScroll = ui->Previewer;

  colorPallet->setClearColor(QColor(240,240,240));
  towerGrid->setClearColor(Qt::white);
  windowScroll->setClearColor(QColor(240,240,240));
}
