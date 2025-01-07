#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N];
void dfs(int u,int fa,int val){
	dep[u]=val;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u,val^1);
	}
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)first[i]=0,dep[i]=0;
	cnt=0;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	dfs(1,0,0);
	int cnt[2]={0,0};
	for(int i=1;i<=n;i++)cnt[dep[i]]++;
	int val[3]={3,1,2};
	if(cnt[0]>n/3&&cnt[1]>n/3){
		for(int i=1;i<=n;i++){
			if(val[dep[i]+1]<=n)cout<<val[dep[i]+1]<<" ",val[dep[i]+1]+=3;
			else cout<<val[0]<<" ",val[0]+=3;
		}
		cout<<"\n";
		return;
	}
	for(int i=1;i<=n;i++){
		if(cnt[dep[i]]>cnt[dep[i]^1]){
			if(val[1]<=n)cout<<val[1]<<" ",val[1]+=3;
			else if(val[2]<=n)cout<<val[2]<<" ",val[2]+=3;
			else cout<<val[0]<<" ",val[0]+=3;
		}
		else cout<<val[0]<<" ",val[0]+=3;
	}
	cout<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	solve();
}