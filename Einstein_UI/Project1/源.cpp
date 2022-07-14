#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	int T;
	cin >> T;
	int const N = 100;
	while (T--) {
		int n, m;
		cin >> n >> m;
		int a[N];
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		int res = 0;
		int full;
		for (int i = 0; i < n; i++) {
			full = m;
			if (a[i] == 0)continue;
			res++;
			for (int j = i; j < n; j++) {
				if (a[j] > full || a[j] == 0)break;
				else {
					full = full - a[j]; a[j] = 0;
				}
			}
			

		}
		cout << res << endl;
	}
}