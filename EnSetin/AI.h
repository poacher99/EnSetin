#pragma once
#include"pre_Define.h"
#include"Referee.h"


class AI {
public:
	Referee* judge = new Referee();
	long long all = 0;

	//���캯��
	AI(char b[5][5]);

	//������
	struct tree {
		int fx, fy;
		//�Ƿ��Ѿ�����
		int visit = 0;
		//ʤ������
		double v = 0;
		//���ʴ���
		double n = 0;
		tree* parent = NULL;
		tree* child[6][3] = { NULL };
	};

	//���ؿ�����������������һ������λ��
	pair<int, double> UCT_Search(int fx, int fy);

	//����1-6�����
	int renewRandom();

	//ģ�����嵽����������ʤ��,1Ϊʤ��,campΪ0����
	int Mock(char[5][5], int camp);

	//����
	void back(tree* p, int win, int step);

	//UCTֵ����
	double getUCTvalue(tree* p, int camp);

	//�õ��Ϸ��ƶ���ʽ
	point get_Randommove(point a, int camp);

	//����µ�����ƶ�����
	int getnewrand();

	//ɾ����
	void delete_tree(tree* root);
};