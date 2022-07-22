#include "Game.h"
#include<vector>
#include<ctime>
#pragma warning(disable : 4996)


Game::Game(char b[5][5], int flag, int start)
{
	
	this->flag = flag;
	this->start = start;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)a[i][j] = b[i][j];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)root->now_a[i][j] = a[i][j];

	info[1] = info[1] + "R:A5-";
	info[1] = info[1] + i2a(b[0][0] - 'A' + 1);
	info[1] = info[1] + ";B5-";
	info[1] = info[1] + i2a(b[0][1] - 'A' + 1);
	info[1] = info[1] + ";C5-";
	info[1] = info[1] + i2a(b[0][2] - 'A' + 1);
	info[1] = info[1] + ";A4-";
	info[1] = info[1] + i2a(b[1][0] - 'A' + 1);
	info[1] = info[1] + ";B4-";
	info[1] = info[1] + i2a(b[1][1] - 'A' + 1);
	info[1] = info[1] + ";A3-";
	info[1] = info[1] + i2a(b[2][0] - 'A' + 1);

	info[2] = "B:E3-";
	info[2] = info[2] + i2a(b[4][2] - 'a' + 1);
	info[2] = info[2] + ";D2-";
	info[2] = info[2] + i2a(b[3][3] - 'a' + 1);
	info[2] = info[2] + ";E2-";
	info[2] = info[2] + i2a(b[3][4] - 'a' + 1);
	info[2] = info[2] + ";C1-";
	info[2] = info[2] + i2a(b[4][2] - 'a' + 1);
	info[2] = info[2] + ";D1-";
	info[2] = info[2] + i2a(b[4][3] - 'a' + 1);
	info[2] = info[2] + ";E1-";
	info[2] = info[2] + i2a(b[4][4] - 'a' + 1);

}

void Game::game()
{
	char o_x, o_y, n_x, n_y;
	cout << "请输入敌方队伍名称\n";
	cin >> enemy_name;


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
					//操作存入info
					info[info_index] = "返回到上一回合开始时的棋盘";
					info_index++;

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

			//保存操作到info
			info_save(rand, next.x, next.y, next.x + ai->judge->legal[select].x, next.y + ai->judge->legal[select].y);
			/*outfile.open("output.txt",ios::app);
			outfile << "我方掷得骰子数：" << rand << endl;
			outfile << "我方行棋为： " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "走 " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y<<endl;
			outfile.close();*/


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
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if (cin.fail() == true)cin.clear();
				if ((e_randon < '1' || e_randon>'6')||(c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a' || (tx == c_point.x && ty == c_point.y)) {
					cout << "输入有误，重新输入对手移动的棋子\n"; continue;
				}
				

				//备份移动吃的棋子
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);

				//保存操作到info
				info_save(e_randon-'0', c_point.x, c_point.y, tx, ty);
				/*outfile.open("output.txt", ios::app);
				outfile << "敌方掷得骰子数：" << e_randon << endl;
				outfile << "敌方行棋为： " << c << ' ' << "走 " << tx << ',' << ty << endl;
				outfile.close();*/

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
					//保存操作到info
					info[info_index] = "敌方悔棋";
					info_index++;
					/*outfile.open("output.txt", ios::app);
					outfile << "敌方悔棋"  << endl;
					outfile.close();*/

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
					info[info_index] = "返回到上一回合开始时的棋盘";
					info_index++;
					/*outfile.open("output.txt",ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();*/
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
		int win = ai->judge->End();
		save_game(win);

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
					//保存操作到info
					info[info_index] = "返回到上一回合开始时的棋盘";
					info_index++;
					/*outfile.open("output.txt", ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();*/
					continue;
				}

			}
			//对手行棋
			cout << "请对手移动棋子\n";
			while (1) {
				char c;
				char e_randon;
				cin >> e_randon;
				cin >> c;
				int tx, ty;
				cin >> tx >> ty;
				point c_point = findchessman(c);
				if (cin.fail() == true)cin.clear();
				if ((e_randon > '6' || e_randon < '1')||(c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a'||(tx==c_point.x&&ty==c_point.y)) {
					cout << "输入有误，重新输入对手移动的棋子\n"; continue;
				}
				//备份移动吃的棋子
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);

				//保存操作到info
				info_save(e_randon-'0', c_point.x, c_point.y, tx, ty);
				/*outfile.open("output.txt", ios::app);
				outfile << "敌方掷得骰子数：" << e_randon << endl;
				outfile << "敌方行棋为： " << c << ' ' << "走 " << tx << ',' << ty << endl;
				outfile.close();*/

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

					//保存操作到info
					info[info_index] = "敌方悔棋";
					info_index++;
					/*outfile.open("output.txt", ios::app);
					outfile << "敌方悔棋" << endl;
					outfile.close();*/

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

			//保存操作到info
			info_save(rand, next.x, next.y, next.x + ai->judge->legal[select].x, next.y + ai->judge->legal[select].y);
			/*outfile.open("output.txt", ios::app);
			outfile << "我方掷得骰子数：" << rand << endl;
			outfile << "我方行棋为： " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "走 " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y << endl;
			outfile.close();*/


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
					info[info_index] = "返回到上一回合开始时的棋盘";
					info_index++;
					/*outfile.open("output.txt", ios::app);
					outfile << "退回到上一个回合开始时的棋盘状态" << endl;
					outfile.close();*/
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
		int win = ai->judge->End();
		save_game(win);


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

char Game::i2a(int n)
{
	char c[10] = { '0','1','2','3','4','5','6','7','8','9'};
	return c[n];

}

string Game::i2s(int n)
{
	string c[10] = { "0","1","2","3","4","5","6","7","8","9" };
	return c[n];
}

void Game::info_save(int randon,int fx,int fy,int tx,int ty)
{
	string rand = i2s(randon);
	char ox = x_axis[fx];
	char oy = y_axis[fy];
	char nx = x_axis[tx];
	char ny = y_axis[ty];
	
	info[info_index] =  rand;
	info[info_index] = info[info_index] + ";(";
	info[info_index] = info[info_index] + ox;
	info[info_index] = info[info_index] + oy;
	info[info_index] = info[info_index] + ',';
	info[info_index] = info[info_index] + nx;
	info[info_index] = info[info_index] + ny;
	info[info_index] = info[info_index] + ')';
	info_index++;
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

string Game:: getTime()  //2020-09-11 22:00:49 这个只能到秒
{
	time_t timep;
	time(&timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
	return tmp;
}

void Game::save_game(int win)
{
	string now_time = getTime();
	info[0] = "#[WTN][红方:钝角][蓝方:" + enemy_name;
	info[0] = info[0] + "][";
	if (flag == 1)info[0] = info[0] + "红方先手][";
	else info[0] = info[0] + "蓝方先手][";
	if (win == 1) {
		info[0] = info[0] + "红方胜][";
	}
	else info[0] = info[0] + "蓝方胜][";
	info[0] = info[0] + now_time;
	info[0] = info[0] + " 成都][2022 CCGC]";

	outfile.open("output.txt", ios::app);
	int i = 0;
	while (i < info_index) {
		if (i > 2)outfile << i - 2 << ':';
		outfile << info[i] << endl;
		i++;
	}
	outfile.close();
}

