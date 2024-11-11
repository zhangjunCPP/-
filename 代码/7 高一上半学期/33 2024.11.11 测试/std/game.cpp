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
const int mod=998244353;
ll qpow(ll x,ll y=mod-2,ll ans=1){
	for(;y;(x*=x)%=mod,y>>=1)if(y&1)(ans*=x)%=mod;
	return ans;
}
int n,a,b;
int main(){
	cin>>a>>b,n=a+b;
	cout<<a*qpow(a+b)%mod<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif