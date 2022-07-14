
#include"export.h"
#include"AI.h"
#include"Referee.h"
#include"Game.h"

point findchessman3(int n);
int findchessman3(int fx, int fy);
char findchessname3(int n);


char nowboard[5][5];
AI ai(nowboard);
int nowrandon;
point next_move;
char chessname;

void recive_Board(char a[5][5], int randon)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			nowboard[i][j] = a[i][j];
	nowrandon = randon;
	ai.judge->set_board(nowboard);
	ai.judge->set_new_Board();

	chessMove chessFind = ai.judge->findChessman(nowrandon, 1);
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
		next1 = ai.UCT_Search(chessFind.x.x, chessFind.x.y);
		select = next1.x;
		chessnumber = findchessman3(chessFind.x.x, chessFind.x.y);
	}
	else {
		next1 = ai.UCT_Search(chessFind.x.x, chessFind.x.y);
		next2 = ai.UCT_Search(chessFind.y.x, chessFind.y.y);
		if (next1.y > next2.y) {
			select = next1.first;
			chessnumber = ai.judge->board[chessFind.x.x][chessFind.x.y] - 'A' + 1;
		}
		else {
			select = next2.first;
			chessnumber = ai.judge->board[chessFind.y.x][chessFind.y.y] - 'A' + 1;
		}
	}
	point next = findchessman3(chessnumber);

	next_move = { next.x + ai.judge->legal[select].x ,next.y + ai.judge->legal[select].y };
	char chessname = findchessname3(chessnumber);

	return;
}

char move_PieceName()
{
	
	return chessname;
}

int* get_chessmove()
{
	int a[2] = { next_move.x,next_move.y };
	return a;
}


//���ݱ�Ų�������
point findchessman3(int n) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (nowboard[i][j] == n + 'A' - 1)return { i,j };
		}
}
//����������ұ��
int findchessman3(int fx, int fy) {
	char c = nowboard[fx][fy];
	return c - 'A' + 1;
}

char findchessname3(int n)
{

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (n == nowboard[i][j] - 'A' + 1)return nowboard[i][j];

	return 0;
}