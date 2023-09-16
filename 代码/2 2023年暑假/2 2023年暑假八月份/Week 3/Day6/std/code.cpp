/*---Author:Henry_Huang---*/
#include <bits/stdc++.h>
using namespace std;

int main() {
	
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int a, b;
	cin >> a >> b;
	for (int i = 1; i <= a - 1; ++i)
		cout << '0';
	for (int i = 1; i <= b - 1; ++i)
		cout << '1';
	cout << '\n';
	return 0;
}