#include"AI.h"
#include<algorithm>
#include<cmath>

AI::AI(char b[5][5]) {

	//创建随机数种子
	unsigned seed = time(0);
	srand(seed);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)judge->board[i][j] = b[i][j];
	}
	judge->set_new_Board();
}


pair<int, double> AI::UCT_Search(int fx, int fy) {


	for (int i = 0; i < 3; i++) {
		if (judge->validMove(fx, fy, fx + judge->legal[i].x, fy + judge->legal[i].y,1)) {
			judge->moveChessman(fx, fy, fx + judge->legal[i].x, fy + judge->legal[i].y);
			if (judge->End() == 1)return {i,double(0x0f7f7f7f)};
		}
	}
	judge->set_new_Board();
	//创建根结点
	tree* root = new tree;
	root->fx = fx;
	root->fy = fy;
	int T = 30000;
	while (T--) {
		int if_win;
		judge->set_new_Board();
		tree* p = root;
		//行棋步数
		int step = 0;
		while (1) {

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
				if (p == root) {
					a.x = fx; a.y = fy;
				}
				else {
					a = judge->findChessman2(k + 1, step % 2);
					if (a.x == -1 || a.y == -1)continue;

				}
				if (step > 1)score = -0x7f7f7f7f;
				//选择移动步法
				for (int i = 0; i < 3; i++) {
					if (step % 2 == 1 && judge->validMove(a.x, a.y, a.x + judge->legal[i].x, a.y + judge->legal[i].y, step % 2)) {
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
					if (step % 2 == 0 && judge->validMove(a.x, a.y, a.x - judge->legal[i].x, a.y - judge->legal[i].y, step % 2)) {
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
			if (flag == -1 || flag2 == -1)continue;
			//移动棋子
			if (step % 2)
				judge->moveChessman(tx, ty, tx + judge->legal[flag].x, ty + judge->legal[flag].y);
			else {
				judge->moveChessman(tx, ty, tx - judge->legal[flag].x, ty - judge->legal[flag].y);
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
			if (step % 2) {
				q->fx = tx + judge->legal[flag].x;
				q->fy = ty + judge->legal[flag].y;
			}
			else {
				q->fx = tx - judge->legal[flag].x;
				q->fy = ty - judge->legal[flag].y;
			}
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
		if (judge->validMove(fx, fy, fx + judge->legal[i].x, fy + judge->legal[i].y, 1)) {
			double v = root->child[0][i]->v;
			double n = root->child[0][i]->n;
			double now_score = n;
			if (now_score > score) { score = now_score; flag = i; }
			cout << now_score <<' ' <<v/n<< endl;
		}

	}

	delete_tree(root);
	
	return { flag,score };
}



int AI::Mock(char b[5][5], int camp) {

	//是否结束循环
	int flag = 0;
	//static uniform_int_distribution<int> u(1, 6);
	//static default_random_engine e2;
	while (1) {
		camp = 1 - camp;
		flag = judge->End();
		if (flag == 1 || flag == -1)break;
		point a;
		while (1) {
			int randn = rand() % 6 + 1;
			a = judge->findChessman2(randn, camp);
			if (a.x == -1 || a.y == -1) { 
				flag = judge->End();
				if (flag == 1 || flag == -1)return flag;
				continue;
			}
			break;
		}
		point b = get_Randommove(a, camp);
		judge->moveChessman(a.x, a.y, b.x, b.y);
	}
	return flag;
}




double AI::getUCTvalue(tree* p, int camp) {
	if (camp == 1) {
		double v = p->v;
		double n = p->n;
		return (1.0 * v / n) + sqrt(log(all) / n);
	}
	else {
		double v = p->v;
		double n = p->n;
		return (1.0 * v / n) + sqrt(log(all) / n);
	}
}

point AI::get_Randommove(point a, int camp) {


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
	int now_random = rand()%6+1;
	return now_random;
}

void AI::back(tree* p, int win, int step) {
	if (win != 1)return;
	while (p) {
		p->v++;
		p = p->parent;
	}
	return;
}

int AI::getnewrand() {
	int u = rand() % 3;
	return u;
}

void AI::delete_tree(tree* root)
{

	if (root == NULL)return;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			delete_tree(root->child[i][j]);
		}
	}
	delete root;
}


