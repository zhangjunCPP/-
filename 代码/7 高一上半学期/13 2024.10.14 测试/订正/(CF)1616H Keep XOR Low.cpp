#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=998244353;
int pw[N];
int a[N];
int ch[N][2],tot=1;
int siz[N];
void insert(int x){
	int p=1;
	siz[p]++;
	for(int i=30;i>=0;i--){
		int tmp=(x>>i)&1;
		if(!ch[p][tmp])ch[p][tmp]=++tot;
		p=ch[p][tmp];
		siz[p]++;
	}
}
int dfs(int p1,int p2,int dep,int x){
	if(!p1)return pw[siz[p2]];
	if(!p2)return pw[siz[p1]];
	if(p1==p2){
		if(dep<0)return pw[siz[p1]];
		int ls=ch[p1][0],rs=ch[p1][1];
		if((x>>dep)&1)return dfs(ls,rs,dep-1,x);
		return (dfs(ls,ls,dep-1,x)+dfs(rs,rs,dep-1,x)-1+mod)%mod;
	}
	else{
		if(dep<0)return pw[siz[p1]+siz[p2]];
		int ls_p1=ch[p1][0],rs_p1=ch[p1][1];
		int ls_p2=ch[p2][0],rs_p2=ch[p2][1];
		if((x>>dep)&1)return dfs(ls_p1,rs_p2,dep-1,x)*dfs(rs_p1,ls_p2,dep-1,x)%mod;
		int ans=0;
		ans=(ans+dfs(ls_p1,ls_p2,dep-1,x)+dfs(rs_p1,rs_p2,dep-1,x)-1+mod)%mod;
		ans=(ans+(pw[siz[ls_p1]]-1+mod)*(pw[siz[rs_p1]]-1+mod)%mod)%mod;
		ans=(ans+(pw[siz[ls_p2]]-1+mod)*(pw[siz[rs_p2]]-1+mod)%mod)%mod;
		return ans;
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,x;
	cin>>n>>x;
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)insert(a[i]);
	cout<<(dfs(1,1,30,x)-1+mod)%mod<<"\n";
}