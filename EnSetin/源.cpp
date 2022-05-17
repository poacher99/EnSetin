#include<iostream>
using namespace std;
#include"inter.h"
#include"Referee.h"
#include"AI.h"

//����
char a[5][5]= {{ 'A','B','C','0','0' }, { 'D','E','0','0','0' }, { 'F','0','0','0','f' }, { '0','0','0','e','d' }, { '0','0','c','b','a' }};

//�ƶ�����
void movechessman(int fx, int fy, int tx, int ty,int start);

//׼���׶β�����������
point findchessman(char chessman);

point findchessman(int n);

int main() {
	

	//1��ʼ,0Ϊ׼���׶�
	int start = 0;
	//׼���׶�
	while (1) {
		
		cout << "�Ƿ�ʼ�� ����1��ʼ������0��������" << endl;
		cin >> start;
		if (start == 1)break;
		char chessman1, chessman2;
		cout << "��������Ҫ���������ӱ��" << endl;
		cin >> chessman1 >> chessman2;
		if (abs(chessman1 - chessman2) > 5) { cout << "������ͬһ��Ӫ����" << endl; continue; }
		point c1 = findchessman(chessman1);
		point c2 = findchessman(chessman2);
		movechessman(c1.x, c1.y, c2.x, c2.y, start);
		cout << "��ǰ���̣�\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)cout << a[i][j] << ' ';
			cout << '\n';
		}
	}
	//1���֣�0����
	int flag;
	cout << "ѡ���Ⱥ���" << endl;
	cin >> flag;
	//����
	if (flag) {
		
		int turn = 1;
		while (1) {
			int rand;
			printf("��%d�غϣ�\n", turn);
			AI* ai = new AI(a);
			cout << "�����������õ�������\n";
			cin >> rand;

			//�����������
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j];
				cout << '\n';
			}

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
			cout << "��ǰ����\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << a[i][j];
				cout << '\n';
			}
			
			//�����ƶ�
			cout << "������ƶ�����\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;
				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1) {
					cout << "��������������������ƶ�������\n"; continue;
				}
				movechessman(c_point.x, c_point.y, tx, ty,start);
				break;
			}
			cout << "��ǰ����\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << a[i][j];
				cout << '\n';
			}
			
			int win = ai->judge->End();
			if (win == 1) {
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}
			delete ai->judge;
			delete ai;
			turn++;
		}
	}
	//����
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
//���ݱ�Ų�������
point findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n+'A'-1)return {i,j};
		}
}

