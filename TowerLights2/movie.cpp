#include "movie.h"

Movie::Movie()
{
  frameSquence = new QList <Frame>;
  audio = new QMediaPlayer;
}
