#ifndef PREVIEWER_H
#define PREVIEWER_H

#include <QDialog>

namespace Ui {
class Previewer;
}

class Previewer : public QDialog
{
    Q_OBJECT

public:
    explicit Previewer(QWidget *parent = 0);
    ~Previewer();

private:
    Ui::Previewer *ui;
};

#endif // PREVIEWER_H
