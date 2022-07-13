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

	//����������ı��ĵ�
	infile.open("input.txt", ios::app);
	int play_counts;
	infile >>play_counts;
	infile.close();
	outfile.open("output.txt", ios::app);
	outfile <<'\n' << "��"<<play_counts<<"�֣�" << endl;
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
			printf("��%d�غϣ�\n", turn);
			//�����������
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			cout << '\n';
			//�˻���һ�غ�����
			if (turn > 1) {

				cout << "�Ƿ񷵻���һ�غϵ�����? ����y���أ���������";
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
					//����������ı��ĵ�
					outfile.open("output.txt",ios::app);
					outfile << "�˻ص���һ���غϿ�ʼʱ������״̬"<<endl;
					outfile.close();

					turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					continue;

				}                

			}
			cout << '\n';
			cout << "�����������õ�������\n";
			cin >> rand;
			chessMove chessFind = ai->judge->findChessman(rand, 1);
			//�Ƿ��ҵ���Ӧ����
			int same = 0;
			if (chessFind.x == chessFind.y)same = 1;
			//������һ�����Ӻ��ƶ���ʽ
			pair<int, double> next1, next2;
			//��һ�����ӱ��
			int chessnumber;
			//��һ���ƶ���ʽ
			int select;
			//�����ӽ�������
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

			//����������ı��ĵ�
			outfile.open("output.txt",ios::app);
			outfile << "�ҷ�������������" << rand << endl;
			outfile << "�ҷ�����Ϊ�� " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "�� " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y<<endl;
			outfile.close();


			cout << "��ǰ���̣�\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					//	cout << a[i][j];
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			cout << '\n';
			int win = ai->judge->End();
			if (win == 1) {
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}

			//�����ƶ�
			cout << "��������ֵ������������ƶ�����\n";
			while (1) {
				char c;
				char e_randon;
				cin >> e_randon; 
				if (e_randon < '1' || e_randon>'6') { cout << "��������������������ƶ�������\n"; continue; }
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if (cin.fail() == true)cin.clear();
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a' || (tx == c_point.x && ty == c_point.y)) {
					cout << "��������������������ƶ�������\n"; continue;
				}
				

				//�����ƶ��Ե�����
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);

				//����������ı��ĵ�
				outfile.open("output.txt", ios::app);
				outfile << "�з�������������" << e_randon << endl;
				outfile << "�з�����Ϊ�� " << c << ' ' << "�� " << tx << ',' << ty << endl;
				outfile.close();

				cout << "��ǰ���̣�\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j]<<' ';
					cout << '\n';
				}
				cout << "�Ƿ���壿  ����1����\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;
					//����������ı��ĵ�
					outfile.open("output.txt", ios::app);
					outfile << "�з�����"  << endl;
					outfile.close();

					cout << "��ǰ����\n";
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
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}

			turn++;
			cout << '\n';

			//�˻���һ�غ�����
			if (turn > 1) {

				cout << "�Ƿ񷵻���һ�غϵ�����? ����y���أ���������";
				char c;
				cin >> c;
				if (c == 'y') { 
					back_Board(p); turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					outfile.open("output.txt",ios::app);
					outfile << "�˻ص���һ���غϿ�ʼʱ������״̬" << endl;
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
	//����
	else {

		AI* ai = new AI(a);
		int turn = 1;
		while (1) {
			printf("��%d�غϣ�\n", turn);
			//�����������
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j]<<' ';
				cout << '\n';
			}
			cout << '\n';
			//�˻���һ�غ�����
			if (turn > 1) {

				cout << "�Ƿ񷵻���һ�غϵ�����? ����y���أ���������";
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
					//����������ı��ĵ�
					outfile.open("output.txt", ios::app);
					outfile << "�˻ص���һ���غϿ�ʼʱ������״̬" << endl;
					outfile.close();
					continue;
				}

			}
			//��������
			cout << "������ƶ�����\n";
			while (1) {
				char c;
				char e_randon;
				cin >> e_randon;
				if (e_randon > '6' || e_randon < '1') {
					cout << "��������������������ƶ�������\n";
					continue;
				}
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if (cin.fail() == true)cin.clear();
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a'||(tx==c_point.x&&ty==c_point.y)) {
					cout << "��������������������ƶ�������\n"; continue;
				}
				//�����ƶ��Ե�����
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);

				//����������ı��ĵ�
				outfile.open("output.txt", ios::app);
				outfile << "�з�������������" << e_randon << endl;
				outfile << "�з�����Ϊ�� " << c << ' ' << "�� " << tx << ',' << ty << endl;
				outfile.close();

				cout << "��ǰ����\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j]<<' ';
					cout << '\n';
				}
				cout << "�Ƿ���壿  ����1����\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;

					//����������ı��ĵ�
					outfile.open("output.txt", ios::app);
					outfile << "�з�����" << endl;
					outfile.close();

					cout << "��ǰ����\n";
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
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}



			//������
			int rand;
			cout << "�����������õ�������\n";
			cin >> rand;


			chessMove chessFind = ai->judge->findChessman(rand, 1);
			//�Ƿ��ҵ���Ӧ����
			int same = 0;
			if (chessFind.x == chessFind.y)same = 1;
			//������һ�����Ӻ��ƶ���ʽ
			pair<int, double> next1, next2;
			//��һ�����ӱ��
			int chessnumber;
			//��һ���ƶ���ʽ
			int select;
			//�����ӽ�������
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

			//����������ı��ĵ�
			outfile.open("output.txt", ios::app);
			outfile << "�ҷ�������������" << rand << endl;
			outfile << "�ҷ�����Ϊ�� " << findchessname(ai->judge->new_board, chessnumber, 1) << ' ' << "�� " << next.x + ai->judge->legal[select].x << ',' << next.y + ai->judge->legal[select].y << endl;
			outfile.close();


			cout << "��ǰ����\n";
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
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}

			turn++;
			cout << '\n';

			//�˻���һ�غ�����
			if (turn > 1) {

				cout << "�Ƿ񷵻���һ�غϵ�����? ����y���أ���������";
				char c;
				cin >> c;
				if (c == 'y') {
					back_Board(p); 
					turn--;
					ai->judge->set_board(a);
					ai->judge->set_new_Board();
					outfile.open("output.txt", ios::app);
					outfile << "�˻ص���һ���غϿ�ʼʱ������״̬" << endl;
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
//���ݱ�Ų�������
point Game:: findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n + 'A' - 1)return { i,j };
		}
}
//����������ұ��
int Game:: findchessman(int fx,int fy) {
	char c = a[fx][fy];
	return c - 'A' + 1;
}



