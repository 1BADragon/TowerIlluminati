#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"
#include <QtGlobal>

#define FULLGRIDWIDTH 12
#define FULLGRIDHEIGHT 20
#define TOWERWIDTH 4
#define TOWERHEIGHT 10

/*!
 * \brief The Frame class
 */
/*!
 * The Frame Class holds data for each individual frame this is
 * a 2D array of pixels.
 */

class Frame
{
public:
    //! Constructor
    Frame();
    //! Copy Constructor
    Frame( const Frame& original);
    //! Setter for the timeStamp member
    void setTimeStamp(qint64 time);
    //! Getter for the timeStamp member
    qint64 getTimeStamp();
    //! Sets the color of a pixel in the 20x12 scale
    void setFullGridPixelColor(int x, int y, QColor c);
    //! Sets the color of a pixel in the 10x4 scale
    void setTowerGridPixel(int x, int y, QColor c);
    //! Get a pixel in the 20x12 scale
    Pixel *FullGridPixel(int x, int y);
    //! Get a pixel in the 10x4 scale
    Pixel *TowerGridPixel(int x, int y);
    //! Shifts the colors of the pixels through a x,y vector
    void applyVector(int x, int y);

private:
    //! Pixel Data matrix pointer
    Pixel* fullGrid[20][12];
    //! Subset of fullGrid
    Pixel* towerGrid[10][4];
    //! The time that a frame is to appear in a movie
    qint64 timeStamp;
};

#endif // FRAME_H
