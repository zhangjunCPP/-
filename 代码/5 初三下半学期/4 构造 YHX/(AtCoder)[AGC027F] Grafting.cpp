#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n;
bool vis[N];
struct Graph{
	struct node{
		int v,nex;
	}a[N];
	int first[N],cnt;
	int deg[N];
	void add(int u,int v){
		a[++cnt]={v,first[u]};
		first[u]=cnt;
		deg[v]++;
	}
	int fa[N];
	void dfs(int u){
		for(int i=first[u];i;i=a[i].nex) {
			int v=a[i].v;
			if(v==fa[u]) continue;
			fa[v]=u;
			dfs(v);
		}
	}
	void init(){
		memset(first,0,sizeof first);
		cnt=0;
		memset(deg,0,sizeof deg);
	}
	int top(){
		int num=0;
		queue<int> q;
		for(int i=1;i<=n;i++)if(vis[i]&&!deg[i]) q.push(i),num++;
		while(!q.empty()){
			int now=q.front();
			q.pop();
			for(int i=first[now];i;i=a[i].nex){
				int v=a[i].v;
				deg[v]--;
				if(!deg[v])q.push(v),num++;
			}
		}
		return num;
	}
}A,B,G;
int ans;
int work(){
	for(int i=1;i<=n;i++) vis[i]=(A.fa[i]!=B.fa[i]);
	int sum=0;
	for(int i=1;i<=n;i++) sum+=vis[i];
	if(sum>=ans) return 0x3f3f3f3f;
	G.init();
	for(int i=1;i<=n;i++){
		if(!vis[i]) {
			if(vis[A.fa[i]]) return 0x3f3f3f3f;
			continue;
		}
		if(vis[A.fa[i]]) G.add(i,A.fa[i]);
		if(vis[B.fa[i]]) G.add(B.fa[i],i);
	}

	if(G.top()==sum) return sum;
	else return 0x3f3f3f3f;
}
void solve(){
	ans=0x3f3f3f3f;
	cin>>n;
	A.init(),B.init();
	for(int i=1;i<n;i++){int u,v;cin>>u>>v;A.add(u,v);A.add(v,u);}
	for(int i=1;i<n;i++){int u,v;cin>>u>>v;B.add(u,v);B.add(v,u);}
	for(int i=1;i<=n;i++){//枚举每个点作为根
		A.fa[i]=0;B.fa[i]=0;
		A.dfs(i);
		B.dfs(i);
		ans=min(ans,work());
		if(A.deg[i]==1){//强制固定移动一个点到i，那么i就不能在动了，这样我们就可以以i作为根
			for(int j=1;j<=n;j++){
				if(i==j)continue;
				A.fa[j]=i;
				A.dfs(j);
				A.fa[i]=0;B.fa[i]=0;
				B.dfs(i);
				ans=min(ans,work()+1);
			}
		}
	}
	if(ans>n)ans=-1;
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}