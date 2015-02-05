#ifndef MOVIE_H
#define MOVIE_H

#include <QList>
#include <QMediaPlayer>

#include "frame.h"

class Movie
{
public:
  Movie();

private:
  QList <Frame> *frameSquence;
  QMediaPlayer *audio;
};

#endif // MOVIE_H
