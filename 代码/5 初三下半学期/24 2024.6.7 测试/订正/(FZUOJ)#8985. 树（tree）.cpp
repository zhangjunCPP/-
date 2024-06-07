#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,block=5000,M=200;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int col[N];
int siz[N];
int p[N],sum;
int pre[M][(1<<16)+5];
int S[M][N];
void dfs(int u,int fa){
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
	if(siz[u]>=block)p[++sum]=u,siz[u]=0;
}
void dfs2(int u,int fa,int s){
	S[s][u]|=1<<col[u];
	++pre[s][S[s][u]];
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		S[s][v]=S[s][u];
		dfs2(v,u,s);
	}
}
int dfs3(int u,int fa,int s){
	int tmp=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa||!(s>>col[v]&1))continue;
		tmp+=dfs3(v,u,s);
	}
	return tmp;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q,c;
	cin>>n>>q>>c;
	for(int i=1;i<=n;i++)cin>>col[i];
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		add(fa,i),add(i,fa);
	}
	dfs(1,0);
	for(int i=1;i<=sum;i++){
		dfs2(p[i],0,i);
		for(int k=0;k<c;k++)for(int s=0;s<(1<<c);s++)if((s>>k)&1)pre[i][s]+=pre[i][s^(1<<k)];
	}
	while(q--){
		int s,u;
		cin>>s>>u;
		if(!((s>>col[u])&1)){cout<<"1\n";continue;}
		bool flag=true;
		for(int k=1;k<=sum;k++)if((s|S[k][u])==s){cout<<pre[k][s]<<"\n";flag=false;break;}
		if(flag)cout<<dfs3(u,0,s)<<"\n";
	}
}