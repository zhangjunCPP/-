#include <bits/stdc++.h>
using namespace std;
int mod = 998244353;
int n, m, f[10010];
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int main()
{
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	int i, x;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= m; i++) f[i] = 0;
	f[0] = 1;
	while(n--){
		scanf("%d", &x);
		for(i = m; i >= x; i--){
			add(f[i], f[i]); add(f[i], f[i - x]);
		}
		for(1; i >= 0; i--) add(f[i], f[i]);
	}
	printf("%d", f[m]);
	return 0;
}
