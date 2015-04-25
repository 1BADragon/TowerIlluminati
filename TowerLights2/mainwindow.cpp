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
            temp->setFullGridPixelColor(i, j, tempC);
        }
    }
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

    qApp->processEvents();
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
