#pragma once
#include"pre_Define.h"
#include"Referee.h"


class AI {
public:
	Referee* judge = new Referee();
	long long all = 0;

	//构造函数
	AI(char b[5][5]);

	//搜索树
	struct tree {
		int fx, fy;
		//是否已经访问
		int visit = 0;
		//胜利次数
		double v = 0;
		//访问次数
		double n = 0;
		tree* parent = NULL;
		tree* child[6][3] = { NULL };
	};

	//蒙特卡洛树搜索，返回下一步走棋位置
	pair<int, double> UCT_Search(int fx, int fy);

	//生成1-6随机数
	int renewRandom();

	//模拟行棋到结束，返回胜负,1为胜利,camp为0先手
	int Mock(char[5][5], int camp);

	//回溯
	void back(tree* p, int win, int step);

	//UCT值计算
	double getUCTvalue(tree* p, int camp);

	//得到合法移动方式
	point get_Randommove(point a, int camp);

	//获得新的随机移动步法
	int getnewrand();

	//删除树
	void delete_tree(tree* root);
};