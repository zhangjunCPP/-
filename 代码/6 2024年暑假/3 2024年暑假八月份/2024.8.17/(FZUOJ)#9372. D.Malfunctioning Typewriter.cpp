#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int ch[N*N][2],tot=1;
int siz[N*N];
void insert(string s) {
	int u=1;
	siz[u]++;
	for(int i=0;i<s.size();i++) {
		int tmp=s[i]-'0';
		if(!ch[u][tmp])ch[u][tmp]=++tot;
		u=ch[u][tmp];
		siz[u]++;
	}
}
double dp[N][N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	double p;
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++) {
		string s;
		cin>>s;
		insert(s);
	}
	for(int i=0;i<=n;i++) {
		for(int j=0;j<=n;j++) {
			if(!i&&!j)dp[i][j]=1;
			else if(!i)dp[i][j]=p*dp[i][j-1];
			else if(!j)dp[i][j]=p*dp[i-1][j];
			else dp[i][j]=max(p*dp[i][j-1]+(1-p)*dp[i-1][j],p*dp[i-1][j]+(1-p)*dp[i][j-1]);
		}
	}
	double ans=1;
	for(int i=1;i<=tot;i++)ans*=dp[siz[ch[i][0]]][siz[ch[i][1]]];
	printf("%.8lf",ans);
}