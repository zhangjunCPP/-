#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,mod=998244853;
int inv[N];
int l[N],r[N];
int sum[N];
int ans=0;
int mul=1;
void add(int l,int r){
	int len=r-l+1;
	mul=mul*len%mod;
	for(int i=l;i<=r;i++){
		ans=(ans+sum[i]*inv[len]%mod+mod)%mod;
		sum[i]=(sum[i]+inv[len])%mod;
	}
}
void del(int l,int r){
	int len=r-l+1;
	mul=mul*inv[len]%mod;
	for(int i=l;i<=r;i++){
		sum[i]=(sum[i]-inv[len]+mod)%mod;
		ans=(ans-sum[i]*inv[len]%mod+mod)%mod;
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	int n,q,v;
	cin>>n>>q>>v;
	for(int i=1;i<=n;i++)cin>>l[i];
	for(int i=1;i<=n;i++)cin>>r[i];
	for(int i=1;i<=n;i++)add(l[i],r[i]);
	cout<<(n*(n+1)/2%mod-ans+mod)%mod*mul%mod<<"\n";
	while(q--){
		int x,y,val;
		cin>>x>>y>>val;
		del(l[y],r[y]);
		if(x==1)l[y]=val;
		else r[y]=val;
		add(l[y],r[y]);
		cout<<(n*(n+1)/2%mod-ans+mod)%mod*mul%mod<<"\n";
	}
}