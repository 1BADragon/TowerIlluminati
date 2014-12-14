#ifndef COLOR_H
#define COLOR_H

#include <QObject>
#include <QColor>

class Color : public QObject
{
  Q_OBJECT
public:
  explicit Color(QObject *parent = 0);
  QColor color;
signals:

public slots:

};

#endif // COLOR_H
