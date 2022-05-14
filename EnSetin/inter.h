#pragma once
#include"pre_Define.h"



//移动棋子
void Move(int fx, int fy, int tx, int ty);

//更新棋盘
void renewBoard(char board[5][5]);

//返回棋盘
char* returnBoard(char board[5][5]);

