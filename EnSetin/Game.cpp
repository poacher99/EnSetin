#include "Game.h"
#include<vector>

Game::Game(char b[5][5], int flag, int start)
{
	
	this->flag = flag;
	this->start = start;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)a[i][j] = b[i][j];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)root->now_a[i][j] = a[i][j];

}

void Game::game()
{

	//保存操作到文本文档
	infile.open("input.txt", ios::app);
	int play_counts;
	infile >>play_counts;
	infile.close();
	outfile.open("output.txt", ios::app);
	outfile <<'\n' << "第"<<play_counts<<"局：" << endl;
	outfile.close();
	outfile.open("input.txt");
	outfile << play_counts+1 << endl;
	outfile.close();


	Board_link* p = root;
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
			//退回上一回合棋盘
			if (turn > 1) {

				cout << "是否返回上一回合的棋盘? 输入y返回，其他继续";
				char c;
				cin >> c;
				if (c == 'y') {
					if (p != root) {
						Board_link* q = p;
						p = p->last;
						delete q;
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)  a[i][j] = p->now_a[i][j];
					}
					//保存操作到文本文档
					outfile.open("output.txt",ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态"<<endl;
					outfile.close();

					turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					continue;

				}                

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
				chessnumber = findchessman(chessFind.x.x,chessFind.x.y);
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

			//保存操作到文本文档
			outfile.open("output.txt",ios::app);
			outfile << "我方掷得骰子数：" << rand << endl;
			outfile << "我方行棋为： " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "走 " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y<<endl;
			outfile.close();


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
			cout << "请输入对手的骰子数，并移动棋子\n";
			while (1) {
				char c;
				char e_randon;
				cin >> e_randon; 
				if (e_randon < '1' || e_randon>'6') { cout << "输入有误，重新输入对手移动的棋子\n"; continue; }
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

				//保存操作到文本文档
				outfile.open("output.txt", ios::app);
				outfile << "敌方掷得骰子数：" << e_randon << endl;
				outfile << "敌方行棋为： " << c << ' ' << "走 " << tx << ',' << ty << endl;
				outfile.close();

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
					//保存操作到文本文档
					outfile.open("output.txt", ios::app);
					outfile << "敌方悔棋"  << endl;
					outfile.close();

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

			//退回上一回合棋盘
			if (turn > 1) {

				cout << "是否返回上一回合的棋盘? 输入y返回，其他继续";
				char c;
				cin >> c;
				if (c == 'y') { 
					back_Board(p); turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					outfile.open("output.txt",ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();
				}
				else {
					Board_link* q=new Board_link;
					q->last = p;
					for (int i = 0; i < 5; i++)
						for (int j = 0; j < 5; j++)q->now_a[i][j] = a[i][j];
					p = q;
				}

			}
		}
		delete_board(p);
		delete ai->judge;
		delete ai;
	}
	//后手
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
			cout << '\n';
			//退回上一回合棋盘
			if (turn > 1) {

				cout << "是否返回上一回合的棋盘? 输入y返回，其他继续";
				char c;
				cin >> c;
				if (c == 'y') {
					if (p != root) {
						Board_link* q = p;
						p = p->last;
						delete q;
						for (int i = 0; i < 5; i++)
							for (int j = 0; j < 5; j++)  a[i][j] = p->now_a[i][j];
					}
					turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					//保存操作到文本文档
					outfile.open("output.txt", ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();
					continue;
				}

			}
			//对手行棋
			cout << "请对手移动棋子\n";
			while (1) {
				char c;
				char e_randon;
				cin >> e_randon;
				if (e_randon > '6' || e_randon < '1') {
					cout << "输入有误，重新输入对手移动的棋子\n";
					continue;
				}
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

				//保存操作到文本文档
				outfile.open("output.txt", ios::app);
				outfile << "敌方掷得骰子数：" << e_randon << endl;
				outfile << "敌方行棋为： " << c << ' ' << "走 " << tx << ',' << ty << endl;
				outfile.close();

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

					//保存操作到文本文档
					outfile.open("output.txt", ios::app);
					outfile << "敌方悔棋" << endl;
					outfile.close();

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
				chessnumber = findchessman(chessFind.x.x,chessFind.x.y);
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

			//保存操作到文本文档
			outfile.open("output.txt", ios::app);
			outfile << "我方掷得骰子数：" << rand << endl;
			outfile << "我方行棋为： " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "走 " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y << endl;
			outfile.close();


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

			//退回上一回合棋盘
			if (turn > 1) {

				cout << "是否返回上一回合的棋盘? 输入y返回，其他继续";
				char c;
				cin >> c;
				if (c == 'y') {
					back_Board(p); 
					turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					outfile.open("output.txt", ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();
				}
				else {
					Board_link* q = new Board_link;
					q->last = p;
					for (int i = 0; i < 5; i++)
						for (int j = 0; j < 5; j++)q->now_a[i][j] = a[i][j];
					p = q;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
				}

			}
		}
		delete_board(p);
		delete ai->judge;
		delete ai;
	}
	return;
}

void Game::back_Board(Board_link* p)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)  a[i][j]=p->now_a[i][j];
	
}

void Game::delete_board(Board_link* p)
{
	if (p == NULL)return;
	Board_link* q = p->last;
	delete p;
	return delete_board(q);
}

char Game::findchessname(char b[5][5], int n, int team)
{

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (team == 1) {
				if (n == b[i][j] - 'A' + 1)return b[i][j];
			}
			else if (n == b[i][j] - 'a' + 1)return b[i][j];

	return 0;
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
//根据坐标查找编号
int Game:: findchessman(int fx,int fy) {
	char c = a[fx][fy];
	return c - 'A' + 1;
}



