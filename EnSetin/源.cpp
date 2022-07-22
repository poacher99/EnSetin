#include<iostream>
using namespace std;
#include"Referee.h"
#include"AI.h"
#include"Game.h"

//����
char a[5][5] = { { 'A','B','C','0','0' }, { 'D','E','0','0','0' }, { 'F','0','0','0','f' }, { '0','0','0','e','d' }, { '0','0','c','b','a' } };

//�ƶ�����
void movechessman(int fx, int fy, int tx, int ty, int start);

//׼���׶β�����������
point findchessman(char chessman);

point findchessman(int n);


int main() {

	cout << "��ǰ���̣�\n";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)cout << a[i][j] << ' ';
		cout << '\n';
	}
	//1��ʼ,0Ϊ׼���׶�
	int start = 0;
	//׼���׶�
	while (1) {
		

		cout << "�Ƿ�ʼ�� ����1��ʼ������0��������" << endl;
		cin >> start;
		if (start == 1)break;
		char chessman1, chessman2;
		while (1) {
			cout << "��������Ҫ���������ӱ��(��ɫ������A-F����ɫ������a-f)" << endl;
			cin >> chessman1 >> chessman2;
			if ((chessman1 >= 'A' && chessman2 <= 'F') || (chessman1 >= 'a' && chessman2 <= 'f'))break;
			else cout << "������������ȷ�ĸ�ʽA-F��a-f";
		}
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
	cout << "ѡ���Ⱥ���: (����1���֣�����0����)" << endl;
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
//���ݱ�Ų�������
point findchessman(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (a[i][j] == n + 'A' - 1)return { i,j };
		}
}

