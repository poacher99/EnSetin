#pragma once
#include"pre_Define.h"
#include<random>
#include<time.h>

class Referee {
public:
	char board[5][5];
	//合法移动方式
	point legal[3] = {
			{0,1},{1,0},{1,1}
	};
	

	//设置初始棋盘
	void set_Board(char);

	
		

	//当前随机数
	int now_random = 0;



	//所属阵营,1为左上，-1为右下，0为没有棋子
	int owner(int fx, int fy);

	//判断移动是否合法,1为合法，0为非法
	int validMove(int fx, int fy, int tx, int ty);

	//判断胜利或者失败,0继续，-1失败，1胜利
	int End();
};