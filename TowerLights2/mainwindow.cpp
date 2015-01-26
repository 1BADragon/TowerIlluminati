#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cWheel = new ColorWheel(ui->colorWheelWidget);

    cWheel->show();
    cWheel->size();
    ui->colorWheelWidget->show();
    ui->TowerGrid->rootContext()->setContextProperty("currentColor", cWheel);

    red = ui->redSpinBox;
    blue = ui->blueSpinBox;
    green = ui->greenSpinBox;

    red->setValue(cWheel->color().red());
    blue->setValue(cWheel->color().blue());
    green->setValue(cWheel->color().green());

    connect(cWheel, SIGNAL(colorChange(QColor)),
            this, SLOT(updateColorSpinBoxes(QColor)));
    ping = true;
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
    cWheel->setColor(temp);
    ping = true;
    std::cout << "rspinbox\n";
}

void MainWindow::on_blueSpinBox_valueChanged(int arg1)
{
    QColor temp = cWheel->color();
    temp.setBlue(arg1);
    cWheel->setColor(temp);
    ping = true;
}

void MainWindow::on_greenSpinBox_valueChanged(int arg1)
{
    QColor temp = cWheel->color();
    temp.setGreen(arg1);
    cWheel->setColor(temp);
    ping = true;
}

void MainWindow::updateColorSpinBoxes(QColor newColor){
  if(ping == false){
    red->setValue(newColor.red());
    green->setValue(newColor.green());
    blue->setValue(newColor.blue());
    std::cout<<"colorwheel\n";
    ping = true;
  }else {
    ping = false;
  }
}
