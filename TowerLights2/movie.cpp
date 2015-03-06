#include "movie.h"

Movie::Movie()
{
  frameSequence = new QList <Frame*>;
  currentIndex = 0;
  currentFrameNumber = 0;
}

void Movie::setAudio(QUrl url)
{
  audioFile = url;
  //load audio player
}

QUrl Movie::getAudioFile()
{
  return audioFile;
}

int Movie::getFrameCount()
{
  return frameSequence->length();
}

void Movie::newFrame(){
  frameSequence->append(new Frame());
}

void Movie::newFrame(int index){
  frameSequence->insert(index, new Frame());
}

void Movie::insertFrame(int index, Frame *f)
{
  frameSequence->insert(index, f);
}

void Movie::setFrameTime(int index, qint64 time)
{
  frameSequence->at(index)->setTimeStamp(time);
}

Frame* Movie::getNextFrame()
{
    if(currentIndex + 1 < frameSequence->length()){
        return frameSequence->at(currentIndex + 1);
    }
    else
    {
        return NULL;
    }
}

Frame *Movie::getFrame(int i)
{
    return frameSequence->at(i);
}

void Movie::reset()
{
  currentIndex = 0;
}

void Movie::setFrame(int index, Frame *f)
{
  (*frameSequence)[index] = f;
}

void Movie::setFile(QUrl url)
{
    mainFile = url;

    //load the file
}

int Movie::getFrameNumber()
{
    return currentFrameNumber;
}

void Movie::setFrameNumber(int x)
{
  currentFrameNumber = x;
}

Frame *Movie::getCurrentFrame()
{
    return (*frameSequence)[currentFrameNumber];
}

void Movie::sortFrames()
{
    qSort(frameSequence->begin(), frameSequence->end(), compareFrames);
}

void Movie::printTimeStamps()
{
    for(int i = 0; i < frameSequence->length(); i++)
    {
        qDebug() << frameSequence->at(i)->getTimeStamp();
    }
}


int compareFrames(const void *a, const void *b)
{
    qint64 aTime = ((Frame*)(a))->getTimeStamp();
    qint64 bTime = ((Frame*)(b))->getTimeStamp();
    return aTime < bTime;
}
