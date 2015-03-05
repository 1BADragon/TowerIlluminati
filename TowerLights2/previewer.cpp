#include "previewer.h"
#include "ui_previewer.h"

Previewer::Previewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Previewer)
{
    ui->setupUi(this);
}

Previewer::~Previewer()
{
    delete ui;
}
