#include<iostream>
using namespace std;
#include"Referee.h"
#include"AI.h"
#include"Game.h"

//棋盘
char a[5][5] = { { 'A','B','C','0','0' }, { 'D','E','0','0','0' }, { 'F','0','0','0','f' }, { '0','0','0','e','d' }, { '0','0','c','b','a' } };

//移动棋子
void movechessman(int fx, int fy, int tx, int ty, int start);

//准备阶段查找棋子坐标
point findchessman(char chessman);

point findchessman(int n);

void game(int flag, int start);

int main() {


	//1开始,0为准备阶段
	int start = 0;
	//准备阶段
	while (1) {

		cout << "是否开始？ 输入1开始，输入0调整棋子" << endl;
		cin >> start;
		if (start == 1)break;
		char chessman1, chessman2;
		cout << "请输入需要交换的棋子编号" << endl;
		cin >> chessman1 >> chessman2;
		if (abs(chessman1 - chessman2) > 5) { cout << "请输入同一阵营棋子" << endl; continue; }
		point c1 = findchessman(chessman1);
		point c2 = findchessman(chessman2);
		movechessman(c1.x, c1.y, c2.x, c2.y, start);
		cout << "当前棋盘：\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)cout << a[i][j] << ' ';
			cout << '\n';
		}
	}
	//1先手，0后手
	int flag;
	cout << "选择先后手" << endl;
	cin >> flag;
		
	Game g(a,flag, start);
	g.game();
	

}


void movechessman(int fx, int fy, int tx, int ty, int start) {
	if (start) {
		a[tx][ty] = a[fx][fy];
		a[fx][fy] = '0';
	}
	else {
		char c = a[tx][ty];
		a[tx][ty] = a[fx][fy];
		a[fx][fy] = c;
	}
	return;
}

point findchessman(char chessman) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == chessman)return { i,j };
		}
}
//根据编号查找坐标
point findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n + 'A' - 1)return { i,j };
		}
}

