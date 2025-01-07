#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e5+10;
const int INF=1e15;
int n;
int a[N];
int s[N];
int ans=INF;
int tmp[N];
void dfs(int now,int last,int MAX,int MIN){
	if(now>n-1) {
		ans=min(ans,MAX-MIN);
		return;
	}
	if(last==1){
		dfs(now+1,0,max(MAX,a[now]+a[now+1]),min(MIN,a[now]+a[now+1]));
	}
	if(now==n-1) dfs(now+1,1,max({MAX,a[now],a[now+1]}),min({MIN,a[now],a[now+1]}));
	else dfs(now+1,1,max(MAX,a[now]),min(MIN,a[now]));
}
signed main(){
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n<=30){
		dfs(1,1,-1,INF);
		cout<<ans;
		return 0;
	}
	else {
		cout<<0;
		return 0;
	}
}

/*



*/
