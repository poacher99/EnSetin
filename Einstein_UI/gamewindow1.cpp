#include "gamewindow1.h"
#include "ui_gamewindow1.h"

gamewindow1::gamewindow1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamewindow1)
{
    ui->setupUi(this);

    //画棋盘线条
    InitUI();

    this->resize((CHESS_C+1)*MAX_X+300,(CHESS_R+1)*MAX_Y+5);
}

gamewindow1::~gamewindow1()
{
    delete ui;
}


void gamewindow1::InitUI()
{
    //定义棋盘大小
    this->resize((CHESS_C+1)*MAX_X,(CHESS_R+1)*MAX_Y);

    this->setWindowTitle("爱恩斯坦棋_人机");
}

void gamewindow1::paintEvent(QPaintEvent *Event)
{
    DrawChessBoard();
}

void gamewindow1::DrawChessBoard()
{
    QPainter painter(this);//绘图工具
    //防止棋盘变形
    painter.setRenderHint(QPainter::HighQualityAntialiasing,true);
    painter.setPen(QPen(QColor(Qt::black),2));//给边框线颜色和大小
    painter.setBrush(Qt::white);//给棋盘格子颜色
    //遍历绘制棋盘的所有的格子
    for(int i=0;i<CHESS_C;i++){
        for(int j=0;j<CHESS_R;j++){
            //绘制矩形（棋盘的格子）
            painter.drawRect((i+0.5)*MAX_X,(j+0.5)*MAX_Y,MAX_X,MAX_Y);
        }
    }
}

void gamewindow1::DrawHandChess(){

}
