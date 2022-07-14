#include "dialog.h"
#include "ui_dialog.h"
#include "gamewindow1.h"
#include "gamewindow2.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    gamewindow1 *game1=new gamewindow1;
    this->close();
    game1->show();
}

void Dialog::on_pushButton_2_clicked()
{
    gamewindow2 *game2=new gamewindow2;
    this->close();
    game2->show();
}

void Dialog::on_pushButton_3_clicked()
{
    this->close();
}
