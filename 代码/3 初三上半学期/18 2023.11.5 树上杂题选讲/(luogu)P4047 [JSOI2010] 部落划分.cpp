#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int u,v;
	double dis;
}a[N];
int cnt;
void add(int u,int v,double dis){a[++cnt]=node{u,v,dis};}
int fa[N];
int find(int x){
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
int cmp(node x,node y){return x.dis<y.dis;}
int x[N],y[N];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)add(i,j,sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2)));
	sort(a+1,a+cnt+1,cmp);
	int sum=0;
	for(int i=1;i<=cnt;i++){
		int fx=find(a[i].u),fy=find(a[i].v);
		if(fx!=fy){
			fa[fx]=fy;
			sum++;
		}
		if(sum==n-k+1){
			printf("%.2lf",a[i].dis);
			return 0;
		}
	}
	return 0;
}