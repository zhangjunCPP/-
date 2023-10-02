#include<bits/stdc++.h>
using namespace std;
const int N=5e7+10;
struct node{
	int x1,y1,x2,y2;
}a[N];
int cnt;
int dx[8]={1,1,0,-1,-1,-1,0,1};
int dy[8]={0,1,1,1,0,-1,-1,-1};
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
	cnt=n;
	for(int i=1;i<=m;i++){
		int v,r,d;
		cin>>v>>r>>d;
		for(int j=0;j<d;j++)a[++cnt]={a[r].x1+j*dx[v],a[r].y1+j*dy[v],a[r].x2+j*dx[v],a[r].y2+j*dy[v]};
		a[r].x1+=d*dx[v];
		a[r].y1+=d*dy[v];
		a[r].x2+=d*dx[v];
		a[r].y2+=d*dy[v];
	}
	while(q--){
		int px,py;
		cin>>px>>py;
		int ans=0;
		for(int i=1;i<=cnt;i++) {
			if(a[i].x1<=px&&a[i].y1<=py&&a[i].x2>=px&&a[i].y2>=py) ans++;
		}
		cout<<ans<<"\n";
	}
}
