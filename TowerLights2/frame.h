/*! \file frame.h
 * \brief This file defines the Frame class as well as the macros
 * FULLGRIDHEIGHT, FULLGRIDWIDTH, TOWERHEIGHT and TOWERWIDTH.
 */
#ifndef FRAME_H
#define FRAME_H

#include "pixel.h"
#include <QtGlobal>

//! Working area's width
#define FULLGRIDWIDTH 12
//! Working area's height
#define FULLGRIDHEIGHT 20
//! Tower's width
#define TOWERWIDTH 4
//! Tower's height
#define TOWERHEIGHT 10

/*!
 * \brief The Frame class
 */
/*!
 * The Frame class contains the data that each frame uses.
 * This data includes the 2D color matricies and the time
 * information for when the frame is appear.
 */

class Frame
{
public:
    //! Constructor
    Frame();
    //! Copy Constructor
    Frame( const Frame& original);
    //! Setter for the timeStamp private memeber
    void setTimeStamp(qint64 time);
    //! Getter for the timeStamp private member
    qint64 getTimeStamp();
    //! Sets a pixel's color based on the full 12x20 grid
    void setFullGridPixelColor(int x, int y, QColor c);
    //! Sets a pixel's color based on the 4x10
    void setTowerGridPixel(int x, int y, QColor c);
    //! Gets a pixel pointer based on the 12x20 coordinate system
    Pixel *FullGridPixel(int x, int y);
    //! Gets a pixel pointer based on the 4x10 coordinate system
    Pixel *TowerGridPixel(int x, int y);
    //! Shifts the pixels in a frame by x y
    void applyVector(int x, int y);

private:
    //! A matrix of pointers that contains pixel data
    Pixel* fullGrid[20][12];
    /*!
     * A subset of fullGrid. Used to point to data only in
     * the main tower. No new data is created this just
     * points to elements allocated in fullGrid
     */
    Pixel* towerGrid[10][4];
    //! Time information for when the fram should appear
    qint64 timeStamp;
};

#endif // FRAME_H
