#ifndef COLORPALETTEASSIGNER_H
#define COLORPALETTEASSIGNER_H
#include <QString>
#include <QObject>


class colorPaletteAssigner : public QObject
{
public:
    Q_INVOKABLE QString getColor();

private:
    int counter;
};

#endif // COLORPALETTEASSIGNER_H
