#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn = 2000010;
int n;
int Min, sum;
int ans[Maxn];
int a[Maxn], l[Maxn], r[Maxn];
int stk[Maxn], tot;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    freopen("sink.in", "r", stdin);
	freopen("sink.out", "w", stdout);
	cin >> n;
	for(int i = 1 ; i <= n ; i++) cin >> a[i];
	for(int i = n + 1 ; i <= 2 * n ; i++) a[i] = a[i - n];
	for(int i = 1 ; i <= 2 * n ; i++){
		while(a[i] <= a[stk[tot]] && tot) tot--;
		l[i] = stk[tot];
		stk[++tot] = i;
	}
	tot = 0;
	for(int i = 2 * n ; i ; i--){
		while(a[i] < a[stk[tot]] && tot) tot--;
		r[i] = stk[tot];
		stk[++tot] = i;
	}
	a[Min] = 1e18;
	for(int i = 1 ; i <= n ; i++){
		if(a[i] < a[Min]) Min = i;
		sum += a[i];
	}
	for(int i = Min + 1 ; i <= Min + n ; i++){
		if(a[i] == a[Min]) continue;
		int x = r[i] - l[i] - 1;
		int y = a[i] - max(a[l[i]], a[r[i]]);
		// cout << i << " " << a[i] << " " << x << " " << y << '\n';
		ans[1] += y;
		ans[1 + x] -= y;
	}
	for(int i = 1 ; i <= n ; i++) ans[i] += ans[i - 1];
	for(int i = 1 ; i <= n ; i++) ans[i] += ans[i - 1];
	for(int i = 1 ; i <= n ; i++) cout << sum - ans[i] << " ";
	cout << '\n';
	return 0;
}
