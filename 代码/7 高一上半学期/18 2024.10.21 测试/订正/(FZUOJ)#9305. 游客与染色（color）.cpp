#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=1e9+7;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int fa[N];
int siz[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int col[N];
vector<int>G[N];
void update(int x){
	col[x]^=1;
	for(int it:G[x])update(it);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=n+m;i++)fa[i]=i,siz[i]=1;
	int ans=qpow(2,n+m-1),inv=qpow(2,mod-2);
	cout<<ans<<"\n";
	while(q--){
		int x,y,color;
		cin>>x>>y>>color;
		y+=n;
		int fx=find(x),fy=find(y);
		if(fx==fy){if((col[x]^col[y])!=color)ans=0;}
		else{
			if(siz[fx]>siz[fy])swap(fx,fy);
			fa[fx]=fy;
			siz[fy]+=siz[fx];
			G[fy].push_back(fx);
			if((col[x]^col[y])!=color)update(fx);
			ans=ans*inv%mod;
		}
		cout<<ans<<"\n";
	}
}