#pragma once
#include"pre_Define.h"
#include"Referee.h"



//搜索树
struct tree {
	int fx, fy;
	//是否已经访问
	int visit = 0;
	//胜利次数
	long long v;
	//访问次数
	long long n;
	tree* parent = NULL;
	tree* child[3];
};

//蒙特卡洛树搜索，返回下一步走棋位置
int UCT_Search(char board[5][5],int fx,int fy);

//生成1-6随机数
int renewRandom();

//模拟行棋到结束，返回胜负
int Mock(char board[5][5]);

//UCT值计算
double getUCTvalue(tree* p);

//得到合法移动方式
point get_Randommove(point a);