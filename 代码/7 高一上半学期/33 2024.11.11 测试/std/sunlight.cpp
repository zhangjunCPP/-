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
const int N=2050;
const ll INF=1e18;
int s,n,a1,b1,a2,b2;
int now=1,las=0;
ll ans,f[2][N];
void update(int i,int x,ll s){
	if(x>=N){
		auto calc=[&](int a,int b){
			ll s=1ll*b*(n-i)-a;
			if(s<0)return 0ll;
			int k=s/b;
			return (k+1)*s-k*(k+1ll)/2*b;
		};
		// debug(i,a1,b1,calc(a1,b1));
		ans=max(ans,s+(n-i+1ll)*x+calc(a1,b1)+calc(a2,b2));
	}else f[now][x]=max(f[now][x],s+x);
}
int main(){
	cin>>s>>n>>a1>>b1>>a2>>b2;
	fill(f[now],f[now]+N,-INF),f[now][0]=s;
	for(int i=1;i<=n&&i<=N*12;i++){
		swap(now,las),fill(f[now],f[now]+N,-INF);
		for(int j=0;j<N;j++){
			if(f[las][j]>=0)update(i,j,f[las][j]);
			if(f[las][j]>=a1)update(i,j+b1,f[las][j]-a1);
			if(f[las][j]>=a2)update(i,j+b2,f[las][j]-a2);
			if(f[las][j]>=a1+a2)update(i,j+b1+b2,f[las][j]-a1-a2);
		}
		if(i==n){
			for(int j=0;j<N;j++)ans=max(ans,f[now][j]);
		}
		if(*max_element(f[now],f[now]+N)<0)break;
	}
	cout<<ans<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif