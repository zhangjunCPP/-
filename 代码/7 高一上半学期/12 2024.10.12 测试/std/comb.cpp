#include<bits/stdc++.h>
using namespace std;

#define MAXN 2050
#define int long long

int sum[MAXN][MAXN],P = 1e9 + 7,C[MAXN][MAXN],pw2[MAXN];

signed main(){
	cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);

	
	double nw = clock();
	int n,q;
	cin >> n >> q;
	for(int i = 0;i <= n;i ++){
		C[i][0] = 1;
		for(int j = 1;j <= i;j ++){
			C[i][j] = (C[i-1][j-1]+C[i-1][j])%P;
		}
	}
	pw2[0] = 1;
	for(int i = 1;i <= n;i ++){
		pw2[i] = pw2[i-1] * 2 % P;
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= i;j ++){
			sum[i][j] = sum[i][j-1] + pw2[i-j]*j%P*j%P*(i-j)%P*C[i][j]%P;
			sum[i][j] %= P;
		}
	}
	for(int i = 1;i <= q;i ++){
		int a,b,c;
		cin >> a >> b >> c;
		cout << (sum[c][b]-sum[c][a-1]+P)%P << '\n';
	}
    cerr << (clock() - nw) / CLOCKS_PER_SEC << '\n';
}
