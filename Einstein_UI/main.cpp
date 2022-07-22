#include "widget.h"
#include <QApplication>
#include<iostream>
#include"export.h"
using namespace std;
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    Widget w;
    w.show();






    return a.exec();
}
