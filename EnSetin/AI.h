#pragma once
#include"pre_Define.h"
#include"Referee.h"



//������
struct tree {
	int fx, fy;
	//�Ƿ��Ѿ�����
	int visit = 0;
	//ʤ������
	long long v;
	//���ʴ���
	long long n;
	tree* parent = NULL;
	tree* child[3];
};

//���ؿ�����������������һ������λ��
int UCT_Search(char board[5][5],int fx,int fy);

//����1-6�����
int renewRandom();

//ģ�����嵽����������ʤ��
int Mock(char board[5][5]);

//UCTֵ����
double getUCTvalue(tree* p);

//�õ��Ϸ��ƶ���ʽ
point get_Randommove(point a);