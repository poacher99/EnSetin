#pragma once
#include"AI.h"

class Game
{
public:
	//��ǰ����
	char a[5][5];
	//��ʽ��ʼ��־
	int start;
	//�Ⱥ���
	int flag;
	Game(char b[5][5], int flag, int start);

	void movechessman(int fx, int fy, int tx, int ty, int start);

	point findchessman(char chessman);

	point findchessman(int n);

	void game();

};

