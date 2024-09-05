#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node {
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v) {
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
double pw[N];
double dp[N];
double Min[N];
struct node2 {
	double val;
	int id;
	bool operator<(const node2&oth)const{return val>oth.val;}
};
bool vis[N];
double sum[N];
int tot[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	pw[0]=1;
	for(int i=1;i<=m;i++)pw[i]=pw[i-1]*0.25;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++)dp[i]=Min[i]=1e9;
	priority_queue<node2>q;
	dp[n]=0;
	q.push({dp[n],n});
	while(!q.empty()) {
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex) {
			int v=a[i].v;
			if(dp[v]==1e9) {
				dp[v]=dp[u]+1.5;
				Min[v]=dp[u];
				sum[v]=1+0.75*dp[u];
				tot[v]++;
				q.push({dp[v],v});
			}
			else {
				if(dp[v]>sum[v]+pw[tot[v]]*(1+0.75*dp[u]+0.25*(2+Min[v]))) {
					dp[v]=sum[v]+pw[tot[v]]*(1+0.75*dp[u]+0.25*(2+Min[v]));
					q.push({dp[v],v});
				}
				sum[v]+=pw[tot[v]]*(1+0.75*dp[u]);
				tot[v]++;
			}
		}
	}
	printf("%.9lf",dp[1]);
}