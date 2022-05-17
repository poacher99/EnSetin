#include"AI.h"
#include<algorithm>
#include<cmath>

AI::AI(char b[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)judge->board[i][j] = b[i][j];
	}
	judge->set_new_Board();
}


pair<int, double> AI::UCT_Search( int fx, int fy) {


	//创建根结点
	tree* root = new tree;
	root->fx = fx;
	root->fy = fy;
	int T = 50;
	if (root->child[0][1]!=NULL&&root->child[0][1]->child[0][1] != NULL)cout << "yes\n";
	while (T--) {
		int if_win;
		judge->set_new_Board();
		tree* p = root;
		//行棋步数
		int step = 0;
		while (p) {
			
			step++;
			all++;
			//记录选择的移动，-1为未选择
			int flag = -1;
			//选择最高分数的棋子
			int flag2 = -1;
			//最高分数
			double score = 0;

			//最高分数棋子初始坐标
			int tx, ty;

			//选择棋子
			int k = 0;
			for (; k < 6; k++) {
				//判断是否退出选择
				int quit = 0;
				point a;
				if (p == root) { a.x = fx; a.y = fy; }
				else {
					a = judge->findChessman2(k, step % 2);
					if (a.x == -1 || a.y == -1)continue;

				}
				//选择移动步法
				for (int i = 0; i < 3; i++) {
					if (judge->validMove(a.x, a.y, a.x + judge->legal[i].x, a.y + judge->legal[i].y,step%2)) {
						if (p->child[k][i] == NULL) {
							flag = i;
							flag2 = k;
							tx = a.x;
							ty = a.y;
							quit = 1;
							break;
						}
						double now_score = getUCTvalue(p->child[k][i], step % 2);
						if (now_score > score) {
							score = now_score; flag = i; flag2 = k;
							tx = a.x; ty = a.y;
						}
					}
				}
				if (step == 1)break;
				if (quit)break;
			}
			//移动棋子
			judge->moveChessman(tx, ty, tx + judge->legal[flag].x, ty + judge->legal[flag].y);
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)cout << judge->new_board[i][j];
				cout << '\n';
			}
			//1为胜利，-1为失败
			if_win = judge->End();
			//找到下一个节点
			if (p->child[flag2][flag] != NULL) {
				tree* q = p->child[flag2][flag];
				q->n++;
				p = q;
				if (if_win != 0) { back(q, if_win, step); break; }
				continue;
			}
			tree* q = new tree;
			q->parent = p;
			q->fx = tx + judge->legal[flag].x;
			q->fy = ty + judge->legal[flag].y;
			q->n++;
			p->child[flag2][flag] = q;
			int win = Mock(judge->new_board, step % 2);
			back(p, win, step);
			break;
		}
	}
	//选择子节点
	int flag = -1;
	double score = 0;
	for (int i = 0; i < 3; i++) {
		if (judge->validMove(fx, fy, fx + judge->legal[i].x, fy + judge->legal[i].y,1)) {
			double now_score = getUCTvalue(root->child[0][i], 1);
			if (now_score > score) { score = now_score; flag = i; }
		}

	}
	return { flag,score };
}



int AI:: Mock(char b[5][5],int camp) {

	//是否结束循环
	int flag=0 ;
	while (1) {
		flag = judge->End();
		if (flag == 1 || flag == -1)break;
		static uniform_int_distribution<int> u(1, 6);
		static default_random_engine e2;
		int rand = u(e2);
		point a = judge->findChessman2(rand, camp);
		if (a.x == -1 || a.y == -1)continue;
		point b = get_Randommove(a, camp);
		judge->moveChessman(a.x, a.y,b.x,b.y);
		camp = 1 - camp;
	}
	return flag;
}


double AI::getUCTvalue(tree* p, int camp) {
	if (camp == 1) {
	int v = p->v;
	int n = p->n;
	return v / n + sqrt(log(all) / n);
	}
	else {
		int v = p->v;
		int n = p->n;
		return (1.0-(v / n)) + sqrt(log(all) / n);
	}
}

point AI::get_Randommove(point a,int camp) {

	
	int fx = a.x, fy = a.y;
	int tx, ty;
	point p;
	while (1) {
		
		int n = getnewrand();
		if (camp == 1) {
			tx = fx + judge->legal[n].x;
			ty = fy + judge->legal[n].y;
			p = { tx,ty };
		}
		else {
			tx = fx - judge->legal[n].x;
			ty = fy - judge->legal[n].y;
			p = { tx,ty };
		}
		int m = judge->legal[n].x;
		int l = judge->legal[n].y;
		if (judge->validMove(fx, fy, tx, ty, camp))return p;
	}

}


int AI::renewRandom() {
	uniform_int_distribution<int> u(1, 6);
	default_random_engine e;
	int now_random = u(e);
	return now_random;
}

void AI:: back(tree* p,int win,int step) {
	if (win != 1)return;
	while (p) {
		p->v++;
		p = p->parent;
	}
	return;
}

int AI::getnewrand() {
	static uniform_int_distribution<int> u(0, 2);
	static default_random_engine e;
	return u(e);
}
