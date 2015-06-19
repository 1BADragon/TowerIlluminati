/*! \file movie.h
 * \brief This file defines the Movie class
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <QList>
#include <QMediaPlayer>

#include "frame.h"

/*!
 * \brief The Movie class
 */
/*!
 * This class is the main class that contains the
 * back-end data used by the creator. It contains the
 * frame sequence as well as indexing and filename info
 * for both the .tan2 and the audio files.
 */
class Movie
{
public:
    //! Constructor
    Movie();
    //! Sets the Audio file's URL
    void setAudio(QUrl url);
    //! Sets the tan file's URL
    void setFile(QUrl url);
    //! Returns the audio files URL
    QUrl getAudioFile();
    //! Return total number of frames
    int getFrameCount();
    //! Creates a new frame at the end of the list
    void newFrame();
    //! Creates a new frame at position index in the list
    void newFrame(int index);
    //! Inserts frame f at position index
    void insertFrame(int index, Frame* f);
    //! Replaces the fram a position index with frame f
    void setFrame(int index, Frame* f);
    //! Sets the time of the frame at posistion index to time
    void setFrameTime(int index, qint64 time);
    //! return the current frame number
    int getFrameNumber();
    //! returns a pointer to the frame after the current frame
    Frame* getNextFrame();
    //! retrns a pointer to the frame at i
    Frame* getFrame(int i);
    //! Sets the current frame back to the beggining
    void reset();
    //! Sets the current frame number to x
    void setFrameNumber(int x);
    //! Returns a pointer to the current frame
    Frame* getCurrentFrame();
    //! Sorts the frames
    void sortFrames();
    //! prints the frames timestamps used for debugging
    void printTimeStamps();
    //! returns the index of the frame at time time
    int getFrameFromTime(int time);
    //! Called to delete the current frame
    void deleteCurrentFrame();

private:
    //! hold the URL of the tan file
    QUrl mainFile;
    //! hold the URL of the audio file
    QUrl audioFile;
    //! A list of the frames in the movie
    QList <Frame*> *frameSequence;

    //! Contains the index of the current frame
    int currentFrameNumber;
};
//! Used for the QSort function. It returns 1, 0, or -1 based on the timestamps of the two frames
int compareFrames(const void* a, const void* b);

#endif // MOVIE_H
