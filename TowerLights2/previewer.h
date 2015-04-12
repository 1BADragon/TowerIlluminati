#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QDialog>
#include "movie.h"
#include "timer.h"
#include <QMediaPlayer>
#include <QQuickItem>

namespace Ui {
class Previewer;
}

class Previewer : public QDialog
{
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = 0);
    ~Previewer();
    void updateData(Movie * movie, QMediaPlayer* audio);


private slots:
    void on_pushButton_clicked();

    void on_horizontalScrollBar_valueChanged(int value);

    void showEvent(QShowEvent* event);

private:
    Ui::Previewer *ui;
    Movie* currentMovie;
    QMediaPlayer* currentAudio;

    QQuickItem *tower[10][4];
    Timer *timer;

    int currentFrameNumber;
    bool stop;

    void setUpMatrix();
    void updateUI();
};

#endif // PREVIEWER_H
