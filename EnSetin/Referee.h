#pragma once
#include"pre_Define.h"
#include<random>
#include<time.h>

class Referee {
public:
	char board[5][5];
	char new_board[5][5];
	//合法移动方式
	point legal[3] = {
			{0,1},{1,0},{1,1}
	};
	
	//设置初始棋盘
	void set_board(char b[5][5]);

	//重置初始棋盘
	void set_new_Board();

	//查找可移动棋子，返回坐标
	pair<point,point> findChessman(int n,int camp);

	//第二层及之后查找棋子,仅仅返回对应的棋子
	point findChessman2(int k, int camp);
		

	//当前随机数
	int now_random = 0;



	//所属阵营,1为左上，-1为右下，0为没有棋子
	int owner(int fx, int fy);

	//判断移动是否合法,1为合法，0为非法
	int validMove(int fx, int fy, int tx, int ty,int camp);

	//给定随机数移动棋子
	void moveChessman(int fx, int fy, int tx, int ty);

	//
	void moveChessman2(int fx, int fy, int tx, int ty);
	

	//判断胜利或者失败,0继续，-1失败，1胜利
	int End();
};