#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
struct node{
	int v,nex;
}a[N*2];
int first[N],cnt;
int deg[N];
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
	deg[v]++;
}
int n,m;
struct node2{
	int u,v,id;
}G[N];
int top[N];
bool top_sort(){
	queue<int> q;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
	int tot=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		top[u]=++tot;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			deg[v]--;
			if(!deg[v])q.push(v);
		}
	}
	if(tot<n)return false;
	return true;
}
int u[N],v[N],w[N];
vector<int> Ans;
bool check(int mid){
	Ans.clear();
	memset(first,0,sizeof first);
	memset(deg,0,sizeof deg);
	cnt=0;
	int tmp=0;
	for(int i=1;i<=m;i++){
		if(w[i]>mid)add(u[i],v[i]);
		else G[++tmp]={u[i],v[i],i};
	}
	if(!top_sort())return false;
	for(int i=1;i<=tmp;i++){
		if(top[G[i].u]>top[G[i].v])Ans.push_back(G[i].id);
	}
	return true;
}
signed main(){
	cin>>n>>m;
	int sum=0;
	for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>w[i],sum+=w[i];
	int l=0,r=sum,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	check(ans);
	cout<<ans<<" "<<Ans.size()<<"\n";
	for(int i:Ans)cout<<i<<" ";
	return 0;
}