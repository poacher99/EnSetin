#pragma once
#include"pre_Define.h"
#include<random>
#include<time.h>

class Referee {
public:
	char board[5][5];
	//�Ϸ��ƶ���ʽ
	point legal[3] = {
			{0,1},{1,0},{1,1}
	};
	

	//���ó�ʼ����
	void set_Board(char);

	
		

	//��ǰ�����
	int now_random = 0;



	//������Ӫ,1Ϊ���ϣ�-1Ϊ���£�0Ϊû������
	int owner(int fx, int fy);

	//�ж��ƶ��Ƿ�Ϸ�,1Ϊ�Ϸ���0Ϊ�Ƿ�
	int validMove(int fx, int fy, int tx, int ty);

	//�ж�ʤ������ʧ��,0������-1ʧ�ܣ�1ʤ��
	int End();
};