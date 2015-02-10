#ifndef MOVIE_H
#define MOVIE_H

#include <QList>
#include <QMediaPlayer>

#include "frame.h"

class Movie
{
public:
  Movie();
  void setAudio(QUrl url);\
  QUrl getAudioFile();

private:
  QUrl mainFile;
  QUrl audioFile;
  QList <Frame> *frameSquence;

  //QMediaPlayer *audio;
};

#endif // MOVIE_H
