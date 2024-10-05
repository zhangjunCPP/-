#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
const int INF=1e7;
int a[N];
int n;
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
map<pair<int,int>,int>mp;
int dfs(int u,int val,int fa){
	if(u>n)return fa;
	if(mp.count({u,val}))return mp[{u,val}];
	int ans;
	if(val<min(a[ls(u)],a[rs(u)]))ans=u;
	else if(a[ls(u)]<a[rs(u)])ans=dfs(ls(u),val,u);
	else if(a[ls(u)]>val)ans=min(dfs(ls(u),val,u),dfs(rs(u),val,u));
	else{
		if(dfs(ls(u),a[ls(u)],u)>dfs(rs(u),a[ls(u)],u))ans=dfs(ls(u),val,u);
		else ans=dfs(rs(u),val,u);
	}
	return mp[{u,val}]=ans;
}
void solve(int x){
	if(x>n)return;
	if(a[x]<min(a[ls(x)],a[rs(x)])){
		solve(ls(x));
		solve(rs(x));
	}
	else if(a[ls(x)]<a[rs(x)]){
		swap(a[x],a[ls(x)]);
		solve(ls(x));
		solve(rs(x));
	}
	else{
		swap(a[x],a[rs(x)]);
		if(a[ls(x)]>a[rs(x)])swap(a[ls(x)],a[rs(x)]);
		if(dfs(ls(x),a[ls(x)],ls(x))>dfs(rs(x),a[ls(x)],rs(x)))swap(a[ls(x)],a[rs(x)]);
		solve(ls(x));
		solve(rs(x));	
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n+1;i<=2*n+1;i++)a[i]=INF;
	solve(1);
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
}