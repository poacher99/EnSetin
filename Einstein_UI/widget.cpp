#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Dialog *dia=new Dialog;
    this->close();
    dia->show();
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}
