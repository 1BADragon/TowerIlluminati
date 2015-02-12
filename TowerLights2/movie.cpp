#include "movie.h"

Movie::Movie()
{
  frameSequence = new QList <Frame*>;
  audio = new QMediaPlayer;
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

Frame* Movie::next()
{
    return frameSequence->at(currentIndex++);
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
