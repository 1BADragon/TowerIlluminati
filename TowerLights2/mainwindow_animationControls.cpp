#include "mainwindow.h"

//Arrow Buttons
void MainWindow::on_upButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(0,1);
    updateMainTower();
    updateUI();
}

void MainWindow::on_downButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(0,-1);
    updateMainTower();
    updateUI();
}

void MainWindow::on_leftButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(1,0);
    updateMainTower();
    updateUI();
}

void MainWindow::on_rightButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(-1,0);
    updateMainTower();
    updateUI();
}

void MainWindow::on_downLeftButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(1,-1);
    updateMainTower();
    updateUI();
}

void MainWindow::on_upLeftButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(1,1);
    updateMainTower();
    updateUI();

}


void MainWindow::on_upRightButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(-1,1);
    updateMainTower();
    updateUI();

}


void MainWindow::on_downRightButton_clicked()
{
    if(QApplication::keyboardModifiers() == Qt::ShiftModifier)
    {
    }
    else
    {
        on_newFrameButton_clicked();
    }
    saveCurrentFrame();
    currentMovie->getCurrentFrame()->applyVector(-1,-1);
    updateMainTower();
    updateUI();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        on_upButton_clicked();
        break;
    case Qt::Key_Down:
        on_downButton_clicked();
        break;
    case Qt::Key_Right:
        on_rightButton_clicked();
        break;
    case Qt::Key_Left:
        on_leftButton_clicked();
        break;
    }
}

void MainWindow::on_actionPreview_Mode_triggered()
{
    this->saveCurrentFrame();
    previewer.updateData(currentMovie, audio);
    previewer.show();
}

void MainWindow::on_actionClose_triggered()
{
    on_actionExit_triggered();
}

void MainWindow::on_mediaSlider_sliderMoved(int position)
{
    ui->previewScrollBar->setValue(currentMovie->getFrameFromTime(position*1000));
}

void MainWindow::on_audioDurationChanged(qint64 duration)
{
    ui->mediaSlider->setRange(0,duration/1000);
    ui->mediaSlider->setValue(currentMovie->getCurrentFrame()->getTimeStamp()/1000);
}

void MainWindow::on_SortButton_clicked()
{
    saveCurrentFrame();
    currentMovie->sortFrames();
    updateMainTower();
    updateUI();
}

//this function is called when file>>exit is selected
void MainWindow::on_actionExit_triggered()
{
    if(edited)
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
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
