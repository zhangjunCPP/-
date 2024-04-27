#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
struct node{
    int val,id;
}a[N];
bool cmp(const node&x,const node&y){return x.val<y.val;}
int ch[N][2],tot=1;
int l[N],r[N];
void insert(int p,int x,int dep,int id){
	if(dep==-1)return;
	int tmp=(x>>dep)&1;
	if(ch[p][tmp])r[ch[p][tmp]]=id;
	else ch[p][tmp]=++tot,l[tot]=r[tot]=id;
	insert(ch[p][tmp],x,dep-1,id);
}
pair<int,int> query(int p,int x,int dep){
	if(dep==-1)return make_pair(0,l[p]);
	int tmp=(x>>dep)&1;
	if(ch[p][tmp])return query(ch[p][tmp],x,dep-1);
	else{
		auto tmp2=query(ch[p][!tmp],x,dep-1);
		tmp2.first+=(1ll<<dep);
		return tmp2;
	}
}
struct node2{
	int v,nex;
}edge[N];
int first[N],cnt;
void add(int u,int v){
	edge[++cnt]={v,first[u]};
	first[u]=cnt;
}
void solve(int p,int dep){
	if(dep==-1)return;
	int ls=ch[p][0],rs=ch[p][1];	
	if(ls&&rs){
		if(r[ls]-l[ls]+1>r[rs]-l[rs]+1)swap(ls,rs);
		int Min=1ll<<60;
		int u,v;
		for(int i=l[ls];i<=r[ls];i++){
			auto tmp=query(rs,a[i].val,dep-1);
			if(Min>tmp.first)Min=tmp.first,u=i,v=tmp.second;
		}		
		add(a[u].id,a[v].id),add(a[v].id,a[u].id);
	}
	if(ls)solve(ls,dep-1);
	if(rs)solve(rs,dep-1);
}
int ans[N];
void dfs(int u,int k){
	ans[u]=k;
	for(int i=first[u];i;i=edge[i].nex){
		int v=edge[i].v;
		if(ans[v]!=-1)continue;
		dfs(v,k^1);
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i].val,a[i].id=i;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)insert(1,a[i].val,30,i);
	solve(1,30);
	for(int i=1;i<=n;i++)ans[i]=-1;
	dfs(1,0);
	for(int i=1;i<=n;i++)cout<<ans[i];
}