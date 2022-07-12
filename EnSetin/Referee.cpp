#include"AI.h"
#include"pre_Define.h"
#include"Referee.h"
#include<cmath>
#include<algorithm>


int Referee::owner(int fx, int fy) {

	if (board[fx][fy] >= 'A' && board[fx][fy] <= 'F')return 1;
	else if (board[fx][fy] == '0')return 0;
	else return -1;

}

void Referee::set_board(char b[5][5])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)this->board[i][j] = b[i][j];
	return;
}

void Referee::set_new_Board() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)this->new_board[i][j] = this->board[i][j];
	}
}



pair<point,point> Referee::findChessman(int num,int camp) {
	chessMove a;
	int t = 0x7f7f7f7f;
	if (camp) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				int temp = abs(new_board[i][j] - 'A' - num + 1);
				if (temp < t) {
					t = temp;
					a.x.first = i; a.x.second = j;
					a.y.first = i; a.y.second = j;
				}
				if (temp == t) { a.y.first = i; a.y.second = j; }
				}
			
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (new_board[i][j] != '0') {
					int temp = abs(new_board[i][j] - 'a' - num + 1);
					if (temp < t) {
						t = temp;
						a.x.first = i; a.x.second = j;
						a.y.first = i; a.y.second = j;
					}
					if (temp == t) { a.y.first = i; a.y.second = j; }
				}
			}
		}
	}
	return a;
}


point Referee::findChessman2(int k, int camp) {
	char chessman_red[7] = { '0','A','B','C','D','E','F' };
	char chessman_blu[7] = { '0','a','b','c','d','e','f' };
	if (camp == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (new_board[i][j] == chessman_red[k])return { i,j };
			}
		}
	}
	if (camp == 0) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (new_board[i][j] == chessman_blu[k])return { i,j };
			}
		}
	}
	return { -1,-1 };
}


int Referee::validMove(int fx, int fy, int tx, int ty,int camp) {
	if (camp == 1) {
		int m = tx - fx + ty - fy;
		if ((tx - fx) > 1 || (ty - fy) > 1)return 0;
		if (m == 0)return 0;
		if (m > 2)return 0;
		if (tx <= 4 && ty <= 4)return 1;
	}
	else {
		if (tx >= 0 && ty >= 0)return 1;
		if ((fx - tx) > 1 && (fy - ty) > 1)return 0;
	}
	return 0;

}

void Referee::moveChessman(int fx, int fy, int tx, int ty) {

	this->new_board[tx][ty] = this->new_board[fx][fy];
	this->new_board[fx][fy] = '0';
	return;
}

int Referee:: End() {
	//flag1为1表示存在红方棋子
	int flag1 = 0, flag2 = 0;
	if (new_board[4][4] >= 'A' && new_board[4][4] <= 'F')return 1;
	else if (new_board[0][0] >= 'a' && new_board[0][0] <= 'f')return -1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (new_board[i][j] >= 'A' && new_board[i][j] <= 'F')flag1 = 1;
			if (new_board[i][j] >= 'a' && new_board[i][j] <= 'f')flag2 = 1;
		}
	}
	if (!flag1)return -1;
	if (!flag2)return 1;

	return 0;

}