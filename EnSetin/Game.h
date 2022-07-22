#pragma once
#include"AI.h"
#include<fstream>
#include<string>
using namespace std;

class Game
{
public:
	//��ǰ����
	char a[5][5];
	ofstream outfile;
	ifstream infile;
	//��������
	int x_axis[5] = { '5','4','3','2','1'};
	char y_axis[5] = { 'A','B','C','D','E' };
	//��������
	string enemy_name;

	//ÿһ�������屣����string������
	string info[100];
	int info_index = 3;

	//����ÿһ�����̵�����
	struct Board_link {
		char now_a[5][5];
		Board_link* next;
		Board_link* last=NULL;
	};
	Board_link* root=new Board_link;
	

	//��ʽ��ʼ��־
	int start;
	//�Ⱥ���
	int flag;
	Game(char b[5][5], int flag, int start);

	void movechessman(int fx, int fy, int tx, int ty, int start);

	point findchessman(char chessman);

	point findchessman(int n);

	//����������ұ��
	int findchessman(int fx, int fy);

	void game();

	//���˵���һ��������
	void back_Board(Board_link* p);

	//ɾ���������������
	void delete_board(Board_link* p);

	//�������ӱ�ŷ�������
	char findchessname(char b[5][5], int n, int team);

	//�Զ���int��charת��
	char i2a(int n);

	//�Զ���int��stringת��
	string i2s(int n);

	//����ÿ����info��
	void info_save(int randon,int fx,int fy,int tx,int ty);

	//��ȡʱ��
	string getTime();

	//��������
	void save_game(int win);

};


