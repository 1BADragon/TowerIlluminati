#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QObject>
#include <QString>

class colorPalette : public QObject
{
  Q_OBJECT
public:
    colorPalette();
    ~colorPalette();
    Q_INVOKABLE QString getColor();

private:
    int count;
};

#endif // COLORPALETTE_H
