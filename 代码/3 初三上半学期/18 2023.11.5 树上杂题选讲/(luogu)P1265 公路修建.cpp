#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int x[N],y[N];
bool vis[N];
double dis[N];
double f(int i,int j) {return sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	for(int i=0;i<=n;i++)dis[i]=1e9;
	dis[1]=0;
	double ans=0;
	for(int i=1; i<=n; i++) {
        int now=0;
		for(int j=1;j<=n;j++)if(dis[j]<dis[now]&&!vis[j])now=j;
		ans+=dis[now],vis[now]=true;
		for(int j=1;j<=n;j++)dis[j]=min(dis[j],f(now,j));
	}
	printf("%.2lf",ans);
	return 0;
}