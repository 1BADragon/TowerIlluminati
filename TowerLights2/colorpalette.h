#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QObject>
#include <QString>

/*!
 * \brief The colorPalette class
 */

/*!
 * This class serves as a helper class to the Color Palette QML code.
 * It keeps track of which color is currently being
 * produced and return a color in accordence.
 */

class colorPalette : public QObject
{
  Q_OBJECT
public:
    colorPalette();
    ~colorPalette();
    Q_INVOKABLE QString getColor();

private:
    int count; /*!< keeps track of the current color */
};

#endif // COLORPALETTE_H
