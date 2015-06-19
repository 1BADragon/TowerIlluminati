#include "mainwindow.h"

//this function is called when file>>new is selected
void MainWindow::on_actionNew_triggered()
{
    if(edited == true)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Your Project?", "Do you want to "
                                             "save your current project?",
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        switch(reply)
        {
        case QMessageBox::Yes:
            on_actionSave_triggered();
        case QMessageBox::No:
            delete currentMovie;
            currentMovie = new Movie();
            currentMovie->newFrame();
            updateMainTower();
            updateUI();
            edited = false;
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
}

//this function is called when file>>open is selected
void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open File"), "/home/", tr("Tan Files (*.tan *.tan2)"));
    if (!fileName.isEmpty())
    {
        delete currentMovie;
        currentMovie= new Movie();
        int version = 0;
        int count = 1;
        int tracker = 6;
        int frameCount = 0;
        int gridLine = 0;

        int skip = 0;
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                skip = 0;
                QString line = in.readLine();
                QRegExp rx("[ :.]");
                QStringList list = line.split(rx, QString::SkipEmptyParts);
                QList <int> nums;
                for(int i = 0; i < list.size(); i++)
                {
                    nums.append(list.at(i).toInt());
                }

                //Get version number
                if(count == 1)
                {
                    if(line == "0.3")
                    {
                        version = 3;
                        //std::cout<< "Version 3" <<std::endl;
                    }
                    if(line == "0.4")
                    {
                        version = 4;
                        //std::cout<< "Version 4" <<std::endl;
                    }
                }

            //Get audio filename
            if(count == 2 && line != "NoAudioFile" && version == 4)
            {
                QUrl temp;
                QString mainfile = QUrl(fileName).fileName();
                qDebug() << line;
                qDebug() << mainfile;
                qDebug() << mainfile.size();
                fileName.chop(mainfile.size());
                line=fileName+line;
                fileName+=mainfile;
                qDebug() << line;
                qDebug() << fileName;
                currentMovie->setAudio(QUrl::fromLocalFile(line));
                audio->setMedia(currentMovie->getAudioFile());
                audio->stop();
            }

                //get current color rgb values for version 3
                if(count == 2 && version == 3)
                {
                    red -> setValue(0);
                    green -> setValue(0);
                    blue -> setValue(0);
                    red -> setValue(nums.at(0));
                    green -> setValue(nums.at(1));
                    blue -> setValue(nums.at(2));
                }


                //get current color rgb values for version 4
                if(count == 3 && version == 4)
                {
                    red -> setValue(0);
                    green -> setValue(0);
                    blue -> setValue(0);
                    red -> setValue(nums.at(0));
                    green -> setValue(nums.at(1));
                    blue -> setValue(nums.at(2));
                }

                //Color Pallet RGB values
                if(count == 4 )
                {
                    int counter = 0;
                    for(int i = 0; i < 2; i++)
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            QColor tempColor;
                            tempColor.setRed(nums.at(counter));
                            counter++;
                            tempColor.setGreen(nums.at(counter));
                            counter++;
                            tempColor.setBlue(nums.at(counter));
                            counter++;
                            colorPallet[i][j]->setProperty("color", tempColor);
                        }
                    }
                }

                //Frame count
                if(count == 5 && version == 4)
                {
                    /*Ignore for now since there is no frame count variable
                   * ...we are currently just using frameSequence -> length();
                  */
                }

                //Add timestamp to frames for version 4
                if(count == tracker  && version == 4)
                {
                    currentMovie->newFrame();
                    currentMovie->getFrame(frameCount)->setTimeStamp(list.at(0).toInt());
                    tracker = tracker + 21;
                    frameCount++;
                    gridLine = 0;
                    skip = 1;
                }

                //Add timestamp to frames for version 3
                if(count == tracker  && version == 3)
                {
                    qint64 tempTime;
                    int minutes = list.at(0).toInt();
                    int seconds = list.at(1).toInt();
                    int millisec = list.at(2).toInt();
                    //std::cout << minutes << " " << seconds << " " << millisec << std::endl;
                    tempTime = minutes*(1000*60) + seconds*1000 + millisec;
                    currentMovie->newFrame();
                    currentMovie->getFrame(frameCount)->setTimeStamp(tempTime);
                    tracker = tracker + 11;
                    frameCount++;
                    gridLine = 0;
                    skip = 1;
                }

                //Add Color info to frames version 4
                if(count < tracker && count > 6 && skip == 0 && version == 4)
                {
                    int counter = 0;
                    for(int i = 0; i < 12; i++)
                    {
                        int tempRed = nums.at(counter);
                        int tempGreen = nums.at(counter + 1);
                        int tempBlue = nums.at(counter + 2);
                        if(tempRed == 0 && tempGreen == 0 && tempBlue == 0)
                        {
                            tempRed = 128;
                            tempGreen = 128;
                            tempBlue = 128;
                        }
                        currentMovie->getFrame(frameCount - 1)->FullGridPixel(gridLine, i)
                                ->setColor(tempRed,tempGreen,tempBlue);
                        /*
                      if(gridLine > 4 && gridLine < 15 && i > 3 && i < 8)
                      {
                          currentMovie->getFrame(frameCount - 1)->TowerGridPixel(gridLine-5, i-4)
                                  ->setColor(tempRed,tempGreen,tempBlue);
                      }
                      */
                        counter = counter + 3;
                    }
                    gridLine++;
                }

                //Add Color info to frames version 3
                if(count < tracker && count > 6 && skip == 0 && version == 3)
                {
                    int tempRed;
                    int tempGreen;
                    int tempBlue;
                    //Populate first rows of full grid before reading more lines
                    if(gridLine < 5)
                    {
                        while(gridLine < 5 )
                        {
                            for(int i = 0; i < 12; i++)
                            {
                                tempRed = 128;
                                tempGreen = 128;
                                tempBlue = 128;
                                currentMovie->getFrame(frameCount - 1)->FullGridPixel(gridLine, i)
                                        ->setColor(tempRed,tempGreen,tempBlue);
                            }
                            gridLine++;
                        }
                    }
                    int counter = 0;
                    for(int i = 0; i < 12; i++)
                    {
                        if(i < 4 || i > 7 || gridLine > 14)
                        {
                            tempRed = 128;
                            tempGreen = 128;
                            tempBlue = 128;
                        }
                        else
                        {
                            tempRed = nums.at(counter);
                            tempGreen = nums.at(counter + 1);
                            tempBlue = nums.at(counter + 2);
                            if(tempRed == 0 && tempGreen == 0 && tempBlue == 0)
                            {
                                tempRed = 128;
                                tempGreen = 128;
                                tempBlue = 128;
                            }
                            counter = counter + 3;
                        }
                        currentMovie->getFrame(frameCount - 1)->FullGridPixel(gridLine, i)
                                ->setColor(tempRed,tempGreen,tempBlue);
                    }
                    gridLine++;
                }

                count++;
            }
            inputFile.close();
        }
        updateMainTower();
        updateUI();
    }
}

//this function is called when file>>export is selected
void MainWindow::on_actionExport_triggered()
{
    saveCurrentFrame();

    //get filename and location for save
    QString exportFileName = QFileDialog::getSaveFileName(this, tr("Export File"),
                                                          "/home/untitled.tan",
                                                          tr("Tan Files (*.tan)"));
    if (!exportFileName.isEmpty())
    {
        // Create a new file
        QFile file(exportFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        //Version Number
        out << "0.3\n";

        //Audio filename
        QUrl tempAF = currentMovie->getAudioFile();
        if(tempAF.isEmpty() == false)
        {
            QFileInfo fileInf(tempAF.toLocalFile());
            QString tempAudioFile = fileInf.fileName();
            out << tempAudioFile << "\n";
        }
        else
        {
            out << "NoAudioFile\n";
        }

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
}

//this function is called when file>>Save As is selected
void MainWindow::on_actionSave_As_triggered()
{
    saveCurrentFrame();

    //get filename and location for save
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                            "/home/untitled.tan2",
                                            tr("Tan Files (*.tan2)"));
    if (!fileName.isEmpty())
    {
        // Create a new file
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        //Version Number
        out << "0.4\n";

        //Audio filename
        QUrl tempAF = currentMovie->getAudioFile();
        if(tempAF.isEmpty() == false)
        {
            QFileInfo fileInf(tempAF.toLocalFile());
            QString tempAudioFile = fileInf.fileName();
            out << tempAudioFile << "\n";
        }
        else
        {
            out << "NoAudioFile\n";
        }

        //Current Color
        out << red->value() << " " << green->value() << " " << blue->value() << "\n";

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
        out << "\n";

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
                                                tr("Tan Files (*.tan2)"));
    }
    // Create a new file
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        //Version Number
        out << "0.4\n";

        //Audio filename
        QUrl tempAF = currentMovie->getAudioFile();
        if(tempAF.isEmpty() == false)
        {
            QFileInfo fileInf(tempAF.toLocalFile());
            QString tempAudioFile = fileInf.fileName();
            out << tempAudioFile << "\n";
        }
        else
        {
            out << "NoAudioFile\n";
        }

        //Current Color
        out << red->value() << " " << green->value() << " " << blue->value() << "\n";

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
        out << "\n";

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
}

void MainWindow::saveWarning()
{
    if(fileName == NULL || fileName == "")
    {
    QMessageBox msgBox;
    msgBox.setText("You've been at it for a while. Would you like to save?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int reply = msgBox.exec();


    switch(reply)
    {
    case QMessageBox::Yes:
        on_actionSave_triggered();
        break;
    case QMessageBox::No:
        break;
    }
    }
    else
    {
        on_actionSave_triggered();
    }

    saveTimer->start();
}
