#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn = 1000010;
int n;
string s;
int pre[Maxn], suf[Maxn];
signed main(){
	ios::sync_with_stdio(false);
	freopen("ant.in", "r", stdin);
	freopen("ant.out", "w", stdout);
	cin >> n >> s;
	s = ' ' + s;
	for(int i = 1 ; i <= n ; i++){
		if(s[i] == 'P') pre[i]++;
		pre[i] += pre[i - 1];
	}
	for(int i = n ; i >= 1 ; i--){
		if(s[i] == 'L') suf[i]++;
		suf[i] += suf[i + 1];
	}
	for(int i = 1 ; i <= n ; i++){
		int x = pre[i - 1], y = suf[i + 1];
		if(x == y){
			cout << x + y << " ";
			continue;
		}
		if(x < y){
			if(s[i] == 'L') cout << 2 * x << " ";
			else cout << 2 * x + 1 << " ";
		}
		if(x > y){
			if(s[i] == 'P') cout << 2 * y << " ";
			else cout << 2 * y + 1 << " ";
		}
	}
	cout << '\n';
	return 0;
}
