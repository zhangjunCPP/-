#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+10;
int cnt,first[N];
struct Edge{
	int u,v,w,nex;
}a[N<<1];
void add(int u,int v,int w){
	a[++cnt]={u,v,w,first[u]};
	first[u]=cnt;
}
int dep[N];
double val[N];
void clf(int u,int dad,int s1,int s0,double mn,bool flag){
	mn=min(mn,1.0*s1/(s1+s0));
	dep[u]=dep[dad]+1;
	if(!a[first[u]].nex&&u!=1)val[u]=(flag?mn:0);
	else if(dep[u]&1)val[u]=-1e9;
	else val[u]=1e9;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v,w=a[i].w;
		if(v!=dad){
			clf(v,u,s1+(w==1),s0+(w==0),mn,u==1?w?1:0:flag);
			if(dep[u]&1)val[u]=max(val[u],val[v]);
			else val[u]=min(val[u],val[v]);
		}
	}
//	if(!flag)val[u]=0;
}
int i,n,x,y,z;
void work(){
	cnt=0;for(i=1;i<=n;++i)first[i]=0;
	scanf("%d",&n);
	for(i=1;i<n;++i){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z),add(y,x,z);
	}
	clf(1,0,0,0,1e9,1);
//	for(i=1;i<=n;++i)printf("val[%d]=%lf\n",i,val[i]);
	printf("%.9lf\n",val[1]);
}
int T;
int main(){
//	while(1);
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
/*
1
11
1 2 1
2 3 0
3 4 0
4 5 1
5 6 1
6 7 1
7 8 1
8 9 1
9 10 1
10 11 0
*/