#include <bits/stdc++.h>
#define int long long
using namespace  std;
const int N=1e5+10;
int n,x,k;
int a[N];
int dis[N];
bool vis[N];
void bfs() {
	queue<int>q;
	for(int i=0;i<n;i++)dis[i]=1e9;
	dis[0]=0;
	q.push(0);
	vis[0]=true;
	while(!q.empty()) {
		int now=q.front();
		q.pop();
		for(int i=1;i<=k;i++) {
			int v=(now-a[i]+n)%n;
			if(!vis[v]) {
				vis[v]=true;
				dis[v]=dis[now]+1;
				q.push(v);
			}
		}
	}
}
signed main() {
	cin>>n>>x>>k;
	for(int i=1;i<=k;i++)cin>>a[i];
	bfs();
	int tmp=dis[x];
	sort(dis,dis+n);
	double ans=tmp;
	int up=tmp,down=1;
	int sum=dis[0];
	for(int i=1;i<=n&&dis[i]<=tmp;i++) {
		if(ans>1.0*(n+sum)/(1.0*i)) {
			ans=1.0*(n+sum)/(1.0*i);
			up=n+sum,down=i;
		}
		sum+=dis[i];
	}
	int GCD=__gcd(up,down);
	cout<<up/GCD<<" "<<down/GCD;
}