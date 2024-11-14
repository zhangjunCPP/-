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
const int N=1e6+10;
int T,n,a[N],vis[N];
void get(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	fill(vis,vis+1+n,0);
	int ans=0,tot=0;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int cnt=0;
		for(int j=i;!vis[j];j=a[j])vis[j]=1,cnt++;
		if(cnt%3==1)ans+=(cnt-1)/3;
		else if(cnt%3==2)ans+=(cnt-2)/3,tot++;
		else ans+=cnt/3;
	}
	ans+=(tot+1)/2;
	printf("%d\n",ans);
}
int main(){
	for(scanf("%d",&T);T--;)get();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif