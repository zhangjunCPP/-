#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int siz[N],son[N],dep[N],fa[N];
void dfs1(int u,int dad){
    siz[u]=1;
    dep[u]=dep[dad]+1;
    fa[u]=dad;
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(v==dad) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
int top[N];
void dfs2(int u){
    if(son[u]){
        int v=son[u];
        top[v]=top[u];
        dfs2(v);
    }
    for(int i=first[u];i;i=a[i].nex){
        int v=a[i].v;
        if(top[v]) continue;
        top[v]=v;
        dfs2(v);
    }
}
int lca(int u,int v){
    int x=top[u],y=top[v];
    while(x!=y){
        if(dep[x]<dep[y]){ swap(x,y), swap(u,v);}
        u=fa[x];
        x=top[u];
    }
    if(dep[u]>dep[v]) swap(u,v);
    return u;
}
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
vector<int> query[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("caterpillar.in","r",stdin);
	freopen("caterpillar.out","w",stdout);
	int n,q;
	cin>>n>>q;
	bool flag1=true,flag2=true;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		if(u>v)swap(u,v);
		if(u!=1)flag1=false;
		add(u,v);
		add(v,u);
	}
	dfs1(1,0);
	top[1]=1;
	dfs2(1);
	for(int i=1;i<=q;i++){
		int T;
		cin>>T;
		if(T!=1)flag2=false;
		for(int j=1;j<=T;j++){int x;cin>>x;query[i].push_back(x);}
	}
	if(flag2){
		for(int i=1;i<=q;i++)cout<<"0\n";
		return 0;
	}
	if(flag1){
		for(int i=1;i<=q;i++){
			if(query[i].size()==1)cout<<"0\n";
			bool flag=false;
			for(int j:query[i])if(j==1){flag=true;break;}
			if(!flag)cout<<"1\n";
			else{
				if(query[i].size()==2)cout<<"0\n";
				else cout<<"1\n";
			}
		}
		return 0;
	}
	for(int i=1;i<=q;i++){
		int ans=1e9;
		for(int u:query[i]){
			int now=0;
			for(int v:query[i]){
				now=max(now,dis(v,lca(u,v)));
			}
			ans=min(ans,now);
		}
		cout<<ans<<"\n";
	}
	return 0;
}