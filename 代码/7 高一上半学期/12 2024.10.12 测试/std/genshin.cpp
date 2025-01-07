#include<bits/stdc++.h>
using namespace std;

#define MAXN 200500

int n,a[MAXN],sum[MAXN];

signed main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
	double nw = clock();
	cin >> n;
	for(int i = 1;i <= n;i ++){
		cin >> a[i];
		sum[i] = sum[i-1] + a[i];
	}
	int ans = 0;
	for(int i = 1;i <= n;i ++){
		for(int j = i - 1;1;j = (j - 1) & (i - 1)){
			ans ^= sum[i]-sum[i-j-1];
			if(!j)break;
		}
	}
	cout << ans << '\n';
	cerr << (clock() - nw) / CLOCKS_PER_SEC << '\n';
}
