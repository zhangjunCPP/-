#include <bits/stdc++.h>
using namespace std;
const int N=60+10,INF=1e9;
int n;
int w[N];
int l[N],r[N];
int a[N];
int ans=-INF;
bool vis[N];
void dfs(int k,int sum) {
	if(!k) {
		sum--;
		int val=0;
		for(int i=1;i<=sum;i++)val+=w[a[i]];
		if(val<=ans)return;
		memset(vis,false,sizeof vis);
		for(int i=1;i<=sum;i++) {
			for(int j=1;j<=a[i];j++) {
				int pos=-1,Min=INF;
				for(int x=1;x<=n;x++)if(!vis[x]&&l[x]<=a[i]&&r[x]>=a[i]&&r[x]<Min)Min=r[x],pos=x;
				if(pos==-1)return;
				vis[pos]=true;
			}
		}
		ans=val;
		return;
	}
	for(int i=max(a[sum-1],1);i<=k;i++)a[sum]=i,dfs(k-i,sum+1);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	for(int i=1;i<=n;i++)cin>>w[i];
	dfs(n,1);
	if(ans==-INF)cout<<"impossible";
	else cout<<ans;
}