#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,q,c;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int col[N];
int siz[N];
void dfs(int u,int fa,int s){
	if(!((s>>(col[u]-1))&1))return;
	siz[u]=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u,s);
		siz[u]+=siz[v];
	}
}
void solve1(){
	while(q--){
		for(int i=1;i<=n;i++)siz[i]=0;
		int s,u;
		cin>>s>>u;
		if(!((s>>(col[u]-1))&1))siz[u]=1;
		else dfs(u,0,s);
		cout<<siz[u]<<"\n";
	}
}
int nxt[N][17],pre[N][17];
void solve2(){
	for(int i=1;i<=c;i++)pre[1][i]=0;
	pre[1][col[1]]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=c;j++)pre[i][j]=pre[i-1][j];
		pre[i][col[i]]=i;
	}
	for(int i=1;i<=c;i++)nxt[n][i]=n+1;
	nxt[n][col[n]]=n;
	for(int i=n-1;i>=1;i--){
		for(int j=1;j<=c;j++)nxt[i][j]=nxt[i+1][j];
		nxt[i][col[i]]=i;
	}
	while(q--){
		int s,u;
		cin>>s>>u;
		if(!((s>>(col[u]-1))&1))cout<<"1\n";
		else{
			int Max=0,Min=n+1;
			for(int i=1;i<=c;i++)if(!((s>>(i-1))&1))Max=max(Max,pre[u][i]),Min=min(Min,nxt[u][i]);
			cout<<Min-Max-1<<"\n";
		}
	}
}
int ans[N][130];
int ans2[50005][1030];
void dfs2_5(int u,int fa,int s,int sum){
	if(!((s>>(col[u]-1))&1))return;
	ans[u][s]=sum;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2_5(v,u,s,sum);
	}
}
void dfs2_10(int u,int fa,int s,int sum){
	if(!((s>>(col[u]-1))&1))return;
	ans2[u][s]=sum;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs2_10(v,u,s,sum);
	}
}
void solve_5(){
	for(int s=0;s<(1<<c);s++){
		for(int u=1;u<=n;u++)siz[u]=0;
		for(int u=1;u<=n;u++){
			if((s>>(col[u]-1))&1){
				if(ans[u][s])continue;
				dfs(u,0,s);
				dfs2_5(u,0,s,siz[u]);
			}
			else ans[u][s]=1;
		}
	}
	while(q--){
		int s,u;
		cin>>s>>u;
		cout<<ans[u][s]<<"\n";
	}
}
void solve_10(){
	for(int s=0;s<(1<<c);s++){
		for(int u=1;u<=n;u++)siz[u]=0;
		for(int u=1;u<=n;u++){
			if((s>>(col[u]-1))&1){
				if(ans2[u][s])continue;
				dfs(u,0,s);
				dfs2_10(u,0,s,siz[u]);
			}
			else ans2[u][s]=1;
		}
	}
	while(q--){
		int s,u;
		cin>>s>>u;
		cout<<ans2[u][s]<<"\n";
	}
}
int main(){
	bool flag=true;
	cin>>n>>q>>c;
	for(int i=1;i<=n;i++)cin>>col[i],col[i]++;
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		if(fa!=i-1)flag=false;
		add(fa,i),add(i,fa);
	}
	if(n<=5000&&q<=5000)solve1();
	else if(flag)solve2();
	else{
		if(n<=50000)solve_10();
		else solve_5();
	}
}