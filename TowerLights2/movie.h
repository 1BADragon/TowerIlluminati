#ifndef MOVIE_H
#define MOVIE_H

#include <QMap>
#include <QMediaPlayer>

#include "frame.h"

class Movie
{
public:
  Movie();

private:
  QMap <qint64, Frame> *frameSquence;
  QMediaPlayer *audio;
};

#endif // MOVIE_H
