#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
	freopen("run.in", "r", stdin);
	freopen("run.out", "w", stdout);
	ll p, a;
	cin >> p >> a;
	if (p & 1) {
		cout << "Impossible\n";
		return 0;
	}
	p /= 2;
	ll x = p / 2, y = p - x;
	if (a < p - 1 || a > x * y) {
		cout << "Impossible\n";
		return 0;
	}
	if (a == x * y) {
		for (int i = 1; i <= x; i++) cout << '2';
		cout << '1';
		for (int i = 2; i <= y; i++) cout << '2';
		cout << '1';
		for (int i = 2; i <= x; i++) cout << '2';
		cout << '1';
		for (int i = 2; i <= y; i++) cout << '2';
		return 0;
	}
	a -= y;
	int pos = 0;
	for (int i = 1; i <= y; i++)
		if (a >= x - 1) a -= x - 1;
		else {
			pos = i;
			break;
		}
	for (int i = 1; i <= x; i++) cout << '2';
	cout << '1';
	for (int i = 2; i <= y; i++) cout << '2';
	cout << '1';
	if (!a) {
		cout << '1';
		for (int i = y - 1; i >= pos; i--) cout << '2';
	} else {
		if (pos != y) {
			cout << '1';
			for (int i = y - 1; i > pos; i--) cout << '2';
			cout << '3';
		} else cout << '2';
		for (int i = 2; i <= a; i++) cout << '2';
		cout << '1';
	}

	cout << '3';
	for (int i = 2; i <= x - 1 - a; i++) cout << '2';
	cout << '1';

	for (int i = pos - 2; i >= 1; i--) cout << '2';
	return 0;
}
