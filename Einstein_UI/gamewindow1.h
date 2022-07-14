#ifndef GAMEWINDOW1_H
#define GAMEWINDOW1_H

#include <QDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QVector>

#define CHESS_R 5//棋盘宽5格，高5格
#define CHESS_C 5
#define MAX_X 120//每个棋子的宽高
#define MAX_Y 120

namespace Ui {
class gamewindow1;
}

class gamewindow1 : public QDialog
{
    Q_OBJECT

public:
    explicit gamewindow1(QWidget *parent = 0);
    ~gamewindow1();
private:
    void InitUI();//初始化界面
    void DrawChessBoard();//画棋盘
    void DrawHandChess();//画鼠标上的棋子
protected:
    void paintEvent(QPaintEvent *event);//实时绘制界面
private:
    Ui::gamewindow1 *ui;
};

#endif // GAMEWINDOW1_H
