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
    //! Constructor
    colorPalette();
    //! Destructor
    ~colorPalette();
    //! Uses the count variable to return a default color pallette value in a hexadecimal value
    Q_INVOKABLE QString getColor();

private:
    /*! keeps track of the current color */
    int count;
};

#endif // COLORPALETTE_H
