#include "gamewindow2.h"
#include "ui_gamewindow2.h"

gamewindow2::gamewindow2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow2)
{
    ui->setupUi(this);
}

gamewindow2::~gamewindow2()
{
    delete ui;
}
