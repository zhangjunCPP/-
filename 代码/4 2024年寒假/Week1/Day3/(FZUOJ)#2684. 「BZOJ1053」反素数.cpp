#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n;
int prime[N]={1,2,3,5,7,11,13,17,19,23,29};
int ans;
int Max;
void dfs(int k,int pre,int last,int now,int sum){
	if(sum>=Max){
		if(sum==Max) ans=min(ans,now);
		else ans=now,Max=sum;
	}
	if(last<pre&&now*prime[k]<=n) dfs(k,pre,last+1,now*prime[k],sum/(last+1)*(last+2));
	if(last&&now*prime[k+1]<=n) dfs(k+1,last,1,now*prime[k+1],sum*2);
}
signed main(){
	cin>>n;
	if(n==1){
		puts("1");
		return 0;
	}
	dfs(1,1000,0,1,1);
	cout<<ans;
}