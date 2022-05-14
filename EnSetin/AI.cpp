#include"AI.h"
#include<algorithm>
#include<cmath>


long long all = 0;
Referee* judge = new Referee();


int UCT_Search(char board[5][5], int fx, int fy) {


	
	tree* root = new tree;
	root->fx = fx;
	root->fy = fy;
	int T = 1e3+5;
	while (T--) {
		tree* p = root;

	}

}



int Mock(char board[5][5]) {

	return 1;

}


double getUCTvalue(tree* p) {
	int v = p->v;
	int n = p->n;
	return v / n + sqrt(log(all) / n);
}

point get_Randommove(point a) {

	uniform_int_distribution<int> u(0, 2);
	default_random_engine e;
	int n = u(e);
	int fx = a.x, fy = a.y;
	int tx = a.x + judge->legal[n].x, ty = a.x + judge->legal[n].y;
	point p = { tx,ty };
	if (judge->validMove(fx, fy, tx, ty))return p;
	return get_Randommove(a);

}


int renewRandom() {
	uniform_int_distribution<int> u(1, 6);
	default_random_engine e;
	int now_random = u(e);
	return now_random;
}