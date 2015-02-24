#ifndef MOVIE_H
#define MOVIE_H

#include <QList>
#include <QMediaPlayer>

#include "frame.h"

class Movie
{
public:
  Movie();
  void setAudio(QUrl url);
  void setFile(QUrl url);
  QUrl getAudioFile();
  int getFrameCount();
  void newFrame();
  void newFrame(int index);
  void insertFrame(int index, Frame* f);
  void setFrame(int index, Frame* f);
  void setFrameTime(int index, qint64 time);
  int getFrameNumber();
  Frame* getNextFrame();
  Frame* getFrame(int i);
  void reset();
  void setFrameNumber(int x);
  int getFrameNumber(int x);
  Frame* getCurrentFrame();
  QMediaPlayer *audio;

private:
  QUrl mainFile;
  QUrl audioFile;
  QList <Frame*> *frameSequence;


  int currentFrameNumber;

  int currentIndex;

  void loadFile();
};

#endif // MOVIE_H
