#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=1e3+10,K=30,M=K*2+1;
int n,a[N];
ll f[N][N][M];
short g[N][N][M];
void chkmin(ll &x,ll y,short &a,short b){
	if(x>y)x=y,a=b;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=K+K;j++)f[i][i][j]=1ll*a[i]*(j-K),g[i][i][j]=i;
	}
	for(int l=n;l>=1;l--){
		for(int r=l+1;r<=n;r++){
			for(int k=1;k<K+K;k++){
				auto calc=[&](int i){
					ll p=f[i+1][r][k+1],q=f[l][i][k-1];
					auto run=[&](ll x){
						if(a[i]<x&&x<=a[i+1]){
							chkmin(f[l][r][k],max(p-x,x+q),g[l][r][k],i);
						}else if(x<=a[i]){
							chkmin(f[l][r][k],max(p-a[i]-1,a[i]+1+q),g[l][r][k],i);
						}else{
							chkmin(f[l][r][k],max(p-a[i+1],a[i+1]+q),g[l][r][k],i);
						}
					};
					if((p-q)%2==0)run((p-q)/2);
					else run((p-q-1)/2),run((p-q+1)/2);
				};
				for(int i=g[l][r-1][k];i<r&&i<=g[l+1][r][k];i++)calc(i);
				// assert(g[l][r][k]>=g[l][r-1][k]&&g[l][r][k]<=g[l+1][r][k]);
			}
		}
		// debug(l);
	}
	cout<<f[1][n][K]<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif