#pragma once
#include"AI.h"

class Game
{
public:
	//当前棋盘
	char a[5][5];
	//正式开始标志
	int start;
	//先后手
	int flag;
	Game(char b[5][5], int flag, int start);

	void movechessman(int fx, int fy, int tx, int ty, int start);

	point findchessman(char chessman);

	point findchessman(int n);

	void game();

};

