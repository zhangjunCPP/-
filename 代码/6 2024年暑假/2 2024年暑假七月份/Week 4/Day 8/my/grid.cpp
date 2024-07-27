#include <bits/stdc++.h>
using namespace std;
int n,m,b;
int f(int x,int y) {return (x-1)*m+y;}
map<int,bool> col;
map<int,int> sum;
int dx[4]={0,-1,0,1};
int dy[4]={1,0,-1,0};
queue<pair<int,int>>q;
int main() {
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	cin>>n>>m>>b;
	long long ans=0;
	while(b--) {
		int x,y;
		cin>>x>>y;
		if(col.count(f(x,y)))continue;
		col[f(x,y)]=true;
		q.push({x,y});
		while(!q.empty()) {
			auto now=q.front();q.pop();
			ans++;
			for(int i=0;i<4;i++) {
				int xx=now.first+dx[i];
				int yy=now.second+dy[i];
				if(xx<1||xx>n||yy<1||yy>m)continue;
				if(col.count(f(xx,yy)))continue;
				sum[f(xx,yy)]++;
				if(sum[f(xx,yy)]==2){col[f(xx,yy)]=true;q.push({xx,yy});}
			}
		}
		// for(int i=1;i<=n;i++) {
		// 	for(int j=1;j<=m;j++) {
		// 		cout<<sum[f(i,j)]<<" ";
		// 	}
		// 	cout<<"\n";
		// }
		// for(auto i:col)cout<<i.first<<" ";
		// cout<<"\tans="<<ans<<"\n";

	}
	cout<<ans;
}