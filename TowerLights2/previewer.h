#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QDialog>
#include "movie.h"
#include "timer.h"
#include <QMediaPlayer>
#include <QQuickItem>

/*!
 * The Ui Namespace is used to by the Qt envoirnment.
 * Its used to be able gather widget data from GUI
 * developed from XML forms.
 */
namespace Ui {
class Previewer;
}

/*!
 * \brief The Previewer class
 */
/*!
 * This class is used to define the look and
 * behavior of the previewer window.
 */
class Previewer : public QDialog
{
    Q_OBJECT

public:
    //! Constructor
    explicit Previewer(QWidget *parent = 0);
    //! Destructor
    ~Previewer();
    //! Updates the pointer for the move and auido data
    void updateData(Movie * movie, QMediaPlayer* audio);


private slots:
    //! slot function connected to the play button on the GUI
    void on_pushButton_clicked();
    //! slot function that is called when the scrollbar's value changes
    void on_horizontalScrollBar_valueChanged(int value);
    //! slot function called when the window is shown
    void showEvent(QShowEvent* event);

private:
    //! used to be able to address the content in the GUI created by the XML forms
    Ui::Previewer *ui;
    //! pointer that points to the movie data in mainWindow
    Movie* currentMovie;
    //! points to the audio data in mainWindow
    QMediaPlayer* currentAudio;

    /*! matrix of the tower windows on the GUI
     * used for easy access
     */
    QQuickItem *tower[10][4];
    //! The previewer uses its own timer so it doesn't interfer with the mainWindow's
    Timer *timer;


    //! Contains the current frame's sequence number
    int currentFrameNumber;
    //! Used in playing to determine whether or not its playing
    bool stop;

    //! Sets up the tower matrix
    void setUpMatrix();
    //! Updates and redraws the GUI
    void updateUI();
};

#endif // PREVIEWER_H
