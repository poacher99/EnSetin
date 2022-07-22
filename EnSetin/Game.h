#pragma once
#include"AI.h"
#include<fstream>
#include<string>
using namespace std;

class Game
{
public:
	//当前棋盘
	char a[5][5];
	ofstream outfile;
	ifstream infile;
	//棋谱坐标
	int x_axis[5] = { '5','4','3','2','1'};
	char y_axis[5] = { 'A','B','C','D','E' };
	//对手名称
	string enemy_name;

	//每一步的走棋保存在string数组中
	string info[100];
	int info_index = 3;

	//保存每一步棋盘的数组
	struct Board_link {
		char now_a[5][5];
		Board_link* next;
		Board_link* last=NULL;
	};
	Board_link* root=new Board_link;
	

	//正式开始标志
	int start;
	//先后手
	int flag;
	Game(char b[5][5], int flag, int start);

	void movechessman(int fx, int fy, int tx, int ty, int start);

	point findchessman(char chessman);

	point findchessman(int n);

	//根据坐标查找编号
	int findchessman(int fx, int fy);

	void game();

	//回退到上一步的棋盘
	void back_Board(Board_link* p);

	//删除保存的所有棋盘
	void delete_board(Board_link* p);

	//根据棋子编号返回名称
	char findchessname(char b[5][5], int n, int team);

	//自定义int到char转化
	char i2a(int n);

	//自定义int到string转化
	string i2s(int n);

	//保存每步到info中
	void info_save(int randon,int fx,int fy,int tx,int ty);

	//获取时间
	string getTime();

	//保存棋谱
	void save_game(int win);

};


