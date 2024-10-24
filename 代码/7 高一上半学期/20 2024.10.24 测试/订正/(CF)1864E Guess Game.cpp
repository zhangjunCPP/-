#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244353;
int tree[N*35][2],tot=1;
int cnt[N*35];
void insert(int x){
	int p=1;
	for(int i=30;i>=0;i--){
		int tmp=(x>>i)&1;
		if(!tree[p][tmp])tree[p][tmp]=++tot;
		p=tree[p][tmp];
		cnt[p]++;
	}
}
int ans;
void dfs(int p,int dep,int sum){
	if(dep==-1){
		ans+=cnt[p]*cnt[p]*(sum+1);
		return;
	}
	if(tree[p][0]&&tree[p][1]&&cnt[tree[p][0]]&&cnt[tree[p][1]])ans+=cnt[tree[p][0]]*cnt[tree[p][1]]*(2*sum+3);
	if(tree[p][0])dfs(tree[p][0],dep-1,sum);
	if(tree[p][1])dfs(tree[p][1],dep-1,sum+1);
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		insert(x);
	}
	ans=0;
	dfs(1,30,0);
	ans%=mod;
	ans=ans*qpow(n,mod-2)%mod*qpow(n,mod-2)%mod;
	cout<<ans<<"\n";
	for(int i=0;i<=tot;i++)tree[i][0]=tree[i][1]=cnt[i]=0;
	tot=1;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}