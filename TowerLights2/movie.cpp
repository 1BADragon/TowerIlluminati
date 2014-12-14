#include "movie.h"

Movie::Movie()
{
  frameSquence = new QMap <qint64,Frame>;
  audio = new QMediaPlayer;
}
