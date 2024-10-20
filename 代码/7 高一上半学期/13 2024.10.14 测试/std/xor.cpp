#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int N=200009;
int n,x,a;
ll ans,pw[N];
int cntnode=1,ch[N*30][2],cnt[N*30];
void insert(){
	int u=1,p; cnt[u]++;
	for(int i=29;i>=0;i--){
		p=((a>>i)&1);
		if(!ch[u][p]) ch[u][p]=++cntnode;
		u=ch[u][p]; cnt[u]++;
	}
	return;
}
ll solve(int u1,int u2,int d){
	if(!u1||!u2) return 0;
	ll re=0,v1,v2;
	int lc1=ch[u1][0],rc1=ch[u1][1],lc2=ch[u2][0],rc2=ch[u2][1];
	if(u1==u2){
		if(d==-1) return pw[cnt[u1]]-1;
		if((x>>d)&1)
			re=pw[cnt[lc1]]-1+pw[cnt[rc1]]-1+solve(lc1,rc1,d-1);
		else
			re=solve(lc1,lc1,d-1)+solve(rc1,rc1,d-1);
		return re%mod;
	}
	else{
		if(d==-1) return (pw[cnt[u1]]-1)*(pw[cnt[u2]]-1)%mod;
		if((x>>d)&1){
			re=(pw[cnt[lc1]]-1)*(pw[cnt[lc2]]-1)%mod+(pw[cnt[rc1]]-1)*(pw[cnt[rc2]]-1)%mod;
			v1=solve(lc1,rc2,d-1); v2=solve(rc1,lc2,d-1);
			re+=v1*(pw[cnt[rc1]]+pw[cnt[lc2]]-1)%mod+v2*(pw[cnt[lc1]]+pw[cnt[rc2]]-1)%mod+v1*v2%mod;
		}
		else
			re=solve(lc1,lc2,d-1)+solve(rc1,rc2,d-1);
		return re%mod;
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	pw[0]=1; for(int i=1;i<N;i++) pw[i]=pw[i-1]*2%mod;
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a,insert();
	ans=solve(1,1,29);
	cout<<ans;
	return 0;
}