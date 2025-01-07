#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6;
unordered_map<int,int> ans_phi,ans_mu;
int prime[N],cnt;
bool vis[N];

int phi[N],mu[N];
void init(){
	phi[1]=mu[1]=1;
	for(int i=2;i<N;i++) {
		if(!vis[i]) {
			prime[++cnt]=i;
			phi[i]=i-1;
			mu[i]=-1;
		}
		for(int j=1;i*prime[j]<N&&j<=cnt;j++) {
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) {
				phi[i*prime[j]]=phi[i]*prime[j];
				mu[i*prime[j]]=0;
				break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=2;i<N;i++) phi[i]+=phi[i-1],mu[i]+=mu[i-1];
}
int get_phi(int x) {
	if(x<N) return phi[x];
	if(ans_phi[x]) return ans_phi[x];
	int ans=x*(x+1)/2;
	for(int l=2,r;l<=x;l=r+1){
		r=x/(x/l);
		ans-=(r-l+1)*get_phi(x/l);
	}
	ans_phi[x]=ans;
	return ans_phi[x];
}
int get_mu(int x) {
	if(x<N) return mu[x];
	if(ans_mu[x]) return ans_mu[x];
	int ans=1;
	for(int l=2,r;l<=x;l=r+1){
		r=x/(x/l);
		ans-=(r-l+1)*get_mu(x/l);
	}
	ans_mu[x]=ans;
	return ans_mu[x];
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	init();
	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		cout<<get_phi(n)<<" "<<get_mu(n)<<"\n";
	}
}