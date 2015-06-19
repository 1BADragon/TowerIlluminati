/*! \file pixel.h
 * \brief This file defines the Pixel class.
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>
#include <QPoint>

/*!
 * \brief The Pixel class.
 */
/*!
 * This class contains the color data
 * of the windows for the data structure that stores the
 * frame sequence.
 */

class Pixel
{
public:
    //! Contructs a Grey Pixel
    Pixel();
    //! Contructs a Pixel Based on the passed QColor value
    Pixel(QColor c);
    //! Sets the pixels color based on rgb colors
    void setColor(int r, int g, int b);
    //! Sets the pixel color based on a QColor value
    void setColor(QColor c);
    //! Returns a QColor value of the current color
    QColor getColor();
    //! Allows = to be used to set pixels
    void operator = (const Pixel& other);
private:
    //! Holds the color of the pixel
    QColor color;
};

#endif // PIXEL_H
