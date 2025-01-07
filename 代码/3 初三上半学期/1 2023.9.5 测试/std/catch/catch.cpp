#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 6;

int read() {
	int s=0,w=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar(); }
	while(isdigit(ch))s=s*10+(ch^48),ch=getchar();
	return s*w;
}
void file(){
	freopen("catch.in","r",stdin);
	freopen("catch.out","w",stdout);
}

vector<int> G[N],cir;
int pre[N],dep[N],top[N],id[N];
int n, q;
bool vis[N],on[N];

bool findcir(int u, int fath) {
	if(vis[u]) {
		int cur = u;
		while(pre[cur]!=u)
			cir.push_back(cur),on[cur]=true,cur=pre[cur];
		cir.push_back(cur),on[cur]=true;
		return true;
	}
	vis[u] = true;
	for(auto v:G[u])if(v^fath){
		pre[v]=u;
		if(findcir(v,u))return true;
	}
	return false;
}
void dfs(int u,int fath,int tp,int d) {
	dep[u]=d,top[u]=tp;
	for(auto v:G[u])if(v^fath&&!on[v])
		dfs(v,u,tp,d+1);
}
int getdis(int a,int b) {
	if(a>b)swap(a,b);
	return min(b-a,a+(int)cir.size()-b);
}

signed main(){
	file();
	n=read(),q=read();
	for(int i=1,u,v;i<=n;++i)
		u=read(),v=read(),
		G[u].push_back(v),
		G[v].push_back(u);
	findcir(1,0);
	
	//for(auto v:cir)cerr<<v<<" ";cerr<<endl;
	
	if(cir.size()<=3){
		for(int i=1,m,c;i<=q;++i)
			m=read(),c=read(),puts("Yes");
		return 0;
	}
	
	for(int i=0;i<(int)cir.size();++i) {
		int v=cir[i];
		id[v]=i;
		dfs(v,0,v,0);
	}
	
	for(int i=1,m,c;i<=q;++i) {
		m=read(),c=read();
		if(top[m]==top[c]) {
			if(dep[m]<dep[c])puts("No");
			else puts("Yes");
			continue;
		}
		int pm=id[top[m]],pc=id[top[c]];
		int dis=getdis(pm,pc);
		if(dep[m]<dep[c]+dis)puts("No");
		else puts("Yes");
	}
	return 0;
}
// 8:20 buhuikaidiguizhankongjian?
