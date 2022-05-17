#include<iostream>
using namespace std;
#include"inter.h"
#include"Referee.h"
#include"AI.h"

//棋盘
char a[5][5]= {{ 'A','B','C','0','0' }, { 'D','E','0','0','0' }, { 'F','0','0','0','f' }, { '0','0','0','e','d' }, { '0','0','c','b','a' }};

//移动棋子
void movechessman(int fx, int fy, int tx, int ty,int start);

//准备阶段查找棋子坐标
point findchessman(char chessman);

point findchessman(int n);

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
	//先手
	if (flag) {
		
		int turn = 1;
		while (1) {
			int rand;
			printf("第%d回合：\n", turn);
			AI* ai = new AI(a);
			cout << "请输入你掷得的骰子数\n";
			cin >> rand;

			//检查输入数组
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j];
				cout << '\n';
			}

			chessMove chessFind = ai->judge->findChessman(rand, 1);
			//是否找到对应棋子
			int same = 0;
			if (chessFind.x == chessFind.y)same = 1;
			//储存下一步棋子和移动方式
			pair<int, double> next1, next2;
			//下一步棋子编号
			int chessnumber;
			//下一步移动方式
			int select;
			//对棋子进行搜索
			if (same) {
				next1 = ai->UCT_Search(chessFind.x.x, chessFind.x.y);
				select = next1.x;
				chessnumber = rand;
			}
			else {
				next1 = ai->UCT_Search(chessFind.x.x, chessFind.x.y);
				next2 = ai->UCT_Search(chessFind.y.x, chessFind.y.y);
				if (next1.y > next2.y) {
					select = next1.first;
					chessnumber = ai->judge->board[chessFind.x.x][chessFind.x.y] - 'A' + 1;
				}
				else {
					select = next2.first;
					chessnumber = ai->judge->board[chessFind.y.x][chessFind.y.y] - 'A' + 1;
				}
			}
			point next = findchessman(chessnumber);
			movechessman(next.x, next.y, next.x + ai->judge->legal[select].x, next.y + ai->judge->legal[select].y, start);
			cout << "当前棋盘\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << a[i][j];
				cout << '\n';
			}
			
			//对手移动
			cout << "请对手移动棋子\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1) {
					cout << "输入有误，重新输入对手移动的棋子\n"; continue;
				}
				movechessman(c_point.x, c_point.y, tx, ty,start);
				break;
			}
			cout << "当前棋盘\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << a[i][j];
				cout << '\n';
			}
			
			int win = ai->judge->End();
			if (win == 1) {
				cout << "你赢了！\n"; break;
			}
			if (win == -1) {
				cout << "对手胜利！\n"; break;
			}
			delete ai->judge;
			delete ai;
			turn++;
		}
	}
	//后手
	else {

	}
	
}


void movechessman(int fx, int fy, int tx, int ty,int start) {
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
	for(int i=0;i<5;i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == chessman)return { i,j };
		}
}
//根据编号查找坐标
point findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n+'A'-1)return {i,j};
		}
}

