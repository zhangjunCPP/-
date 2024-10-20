#include<bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=2e5+5;
int c[maxn],vis[maxn],cnt[maxn];
inline void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*m;i++){
		scanf("%d",&c[i]);
		vis[i]=0;
	}
	for(int i=1;i<=m;i++) cnt[i]=0;
	int ans=n*m;
	int sum=0,mx=0;
	for(int i=2;i<=n*m;i++){
		if(vis[i-1]==0 && c[i]==c[i-1]){
			vis[i]=1;
			cnt[c[i]]++;
			ans--;
			sum++;
		}
	}
	for(int i=1;i<=m;i++) mx=max(mx,cnt[i]);
	if(mx<=sum/2) printf("%d\n",ans);
	else printf("%d\n",ans-(2*mx-sum));
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}