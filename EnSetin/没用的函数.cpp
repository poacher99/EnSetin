/*

void game(int flag, int start) {
	if (flag == 1) {
		AI* ai = new AI(a);
		int turn = 1;
		while (1) {
			int rand;
			printf("��%d�غϣ�\n", turn);
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
			ai->judge->set_board(a);
			ai->judge->set_new_Board();
			cout << "��ǰ����\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					//	cout << a[i][j];
					cout << ai->judge->new_board[i][j];
				cout << '\n';
			}
			int win = ai->judge->End();
			if (win == 1) {
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}

			//�����ƶ�
			cout << "������ƶ�����\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;

				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a') {
					cout << "��������������������ƶ�������\n"; continue;
				}
				//�����ƶ��Ե�����
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);
				cout << "��ǰ����\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j];
					cout << '\n';
				}
				cout << "�Ƿ���壿  ����1����\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;
					cout << "��ǰ����\n";
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++)
							cout << a[i][j];
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
		}
		delete ai->judge;
		delete ai;
	}
	else {

		AI* ai = new AI(a);
		int turn = 1;
		while (1) {
			printf("��%d�غϣ�\n", turn);
			//�����������
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					cout << ai->judge->new_board[i][j];
				cout << '\n';
			}
			//��������
			cout << "������ƶ�����\n";
			while (1) {
				char c;
				cin >> c;
				point c_point = findchessman(c);
				int tx, ty;
				cin >> tx >> ty;

				if ((c_point.x - tx) > 1 || (c_point.y - ty) > 1 || c > 'f' || c < 'a') {
					cout << "��������������������ƶ�������\n"; continue;
				}
				//�����ƶ��Ե�����
				char backup = a[tx][ty];
				movechessman(c_point.x, c_point.y, tx, ty, start);
				cout << "��ǰ����\n";
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++)
						cout << a[i][j];
					cout << '\n';
				}
				cout << "�Ƿ���壿  ����1����\n";
				char s;
				cin >> s;
				if (s == '1') {
					movechessman(tx, ty, c_point.x, c_point.y, start);
					a[tx][ty] = backup;
					cout << "��ǰ����\n";
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 5; j++)
							cout << a[i][j];
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
			cout << "��ǰ����\n";
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++)
					//	cout << a[i][j];
					cout << ai->judge->new_board[i][j];
				cout << '\n';
			}
			win = ai->judge->End();
			if (win == 1) {
				cout << "��Ӯ�ˣ�\n"; break;
			}
			if (win == -1) {
				cout << "����ʤ����\n"; break;
			}

			turn++;
			cout << '\n';
		}
		delete ai->judge;
		delete ai;
	}
	return;
}
*/