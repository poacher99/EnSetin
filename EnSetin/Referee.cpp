#include"AI.h"
#include"inter.h"
#include"pre_Define.h"
#include"Referee.h"
#include<cmath>
#include<algorithm>


int Referee::owner(int fx, int fy) {

	if (board[fx][fy] >= 'A' && board[fx][fy] <= 'F')return 1;
	else if (board[fx][fy] == '0')return 0;
	else return -1;

}

int Referee::validMove(int fx, int fy, int tx, int ty) {
	if ((tx - fx) > 1 || (ty - fy) > 1)return 0;
	if (tx <= 4 && ty <= 4)return 1;
	return 0;

}

int Referee:: End() {
	//flag1为1表示存在红方棋子
	int flag1 = 0, flag2 = 0;
	if (board[4][4] >= 'A' && board[4][4] <= 'F')return 1;
	else if (board[0][0] >= 'a' && board[0][0] <= 'f')return -1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] >= 'A' && board[i][j] <= 'F')flag1 = 1;
			if (board[i][j] >= 'a' && board[i][j] <= 'f')flag2 = 1;
		}
	}
	if (!flag1)return -1;
	if (!flag2)return 1;

	return 0;

}