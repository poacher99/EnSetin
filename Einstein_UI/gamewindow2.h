#ifndef GAMEWINDOW2_H
#define GAMEWINDOW2_H

#include <QDialog>

namespace Ui {
class gamewindow2;
}

class gamewindow2 : public QDialog
{
    Q_OBJECT

public:
    explicit gamewindow2(QWidget *parent = 0);
    ~gamewindow2();

private:
    Ui::gamewindow2 *ui;
};

#endif // GAMEWINDOW2_H
