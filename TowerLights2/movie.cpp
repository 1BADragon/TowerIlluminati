#include "movie.h"

Movie::Movie()
{
  frameSquence = new QList <Frame>;

}

void Movie::setAudio(QUrl url)
{
  audioFile = url;
}

QUrl Movie::getAudioFile()
{
  return audioFile;
}
