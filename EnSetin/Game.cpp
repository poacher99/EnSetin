#include "Game.h"

Game::Game(char b[5][5], int flag, int start)
{

	this->flag = flag;
	this->start = start;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)a[i][j] = b[i][j];

}

void Game::game()
{
	if (flag == 1) {
		AI* ai = new AI(a);
		int turn = 1;
		while (1) {
			int rand;
			printf("第%d回合：\n", turn);
			//检查输入数组
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			cout << '\n';
			cout << "请输入你掷得的骰子数\n";
			cin >> rand;
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
			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			cout << "当前棋盘：\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					//	cout << a[i][j];
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			cout << '\n';
			int win = ai->judge->End();
			if (win == 1) {
				cout << "你赢了！\n"; break;
			}
			if (win == -1) {
				cout << "对手胜利！\n"; break;
			}

			//对手移动
			cout << "请对手移动棋子\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if (cin.fail() == true)cin.clear();
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a' || (tx == c_point.x && ty == c_point.y)) {
					cout << "输入有误，重新输入对手移动的棋子\n"; continue;
				}
				//备份移动吃的棋子
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);
				cout << "当前棋盘：\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j]<<' ';
					cout << '\n';
				}
				cout << "是否悔棋？  输入1悔棋\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;
					cout << "当前棋盘\n";
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++)
							cout << a[i][j]<<' ';
						cout << '\n';
					}
					continue;
				}

				break;
			}

			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			win = ai->judge->End();
			if (win == 1) {
				cout << "你赢了！\n"; break;
			}
			if (win == -1) {
				cout << "对手胜利！\n"; break;
			}

			turn++;
			cout << '\n';
		}
		delete ai->judge;
		delete ai;
	}
	else {

		AI* ai = new AI(a);
		int turn = 1;
		while (1) {
			printf("第%d回合：\n", turn);
			//检查输入数组
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			//对手行棋
			cout << "请对手移动棋子\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if (cin.fail() == true)cin.clear();
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a'||(tx==c_point.x&&ty==c_point.y)) {
					cout << "输入有误，重新输入对手移动的棋子\n"; continue;
				}
				//备份移动吃的棋子
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);
				cout << "当前棋盘\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j]<<' ';
					cout << '\n';
				}
				cout << "是否悔棋？  输入1悔棋\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;
					cout << "当前棋盘\n";
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++)
							cout << a[i][j]<<' ';
						cout << '\n';
					}
					continue;
				}

				break;
			}

			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			int win = ai->judge->End();
			if (win == 1) {
				cout << "你赢了！\n"; break;
			}
			if (win == -1) {
				cout << "对手胜利！\n"; break;
			}



			//你走棋
			int rand;
			cout << "请输入你掷得的骰子数\n";
			cin >> rand;


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
			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			cout << "当前棋盘\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					//	cout << a[i][j];
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			win = ai->judge->End();
			if (win == 1) {
				cout << "你赢了！\n"; break;
			}
			if (win == -1) {
				cout << "对手胜利！\n"; break;
			}

			turn++;
			cout << '\n';
		}
		delete ai->judge;
		delete ai;
	}
	return;
}

void Game::movechessman(int fx, int fy, int tx, int ty, int start) {
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

point Game::findchessman(char chessman) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == chessman)return { i,j };
		}
}
//根据编号查找坐标
point Game:: findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n + 'A' - 1)return { i,j };
		}
}
