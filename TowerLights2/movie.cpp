#include "movie.h"

Movie::Movie()
{
  frameSquence = new QList <Frame*>;
  audio = new QMediaPlayer;
  currentIndex = 0;
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
  return frameSquence->length();
}

void Movie::newFrame(){
  frameSquence->append(new Frame());
}

void Movie::newFrame(int index){
  frameSquence->insert(index, new Frame());
}

void Movie::insertFrame(int index, Frame *f)
{
  frameSquence->insert(index, f);
}

void Movie::setFrameTime(int index, qint64 time)
{
  frameSquence->at(index)->setTimeStamp(time);
}

Frame* Movie::next()
{
  return frameSquence->at(currentIndex++);
}

void Movie::reset()
{
  currentIndex = 0;
}

void Movie::setFrame(int index, Frame *f)
{
  (*frameSquence)[index] = f;
}
