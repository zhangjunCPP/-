#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int a[N];
int vis[N];
struct node{
	int id,val;
};
int main(){ 
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	freopen("manage.in","r",stdin);
	freopen("manage.out","w",stdout);
	int n,m;
	cin>>n>>m; 
	for(int i=1;i<=m;i++) cin>>a[i];
	for(int k=1;k<=n;k++) {
		int ans=0,sum=0;
		queue<node> q;
		for(int i=1;i<=n;i++) vis[i]=0;
		for(int i=1;i<=m;i++) {
			if(vis[a[i]]){
				vis[a[i]]++;
				q.push({a[i],vis[a[i]]});
				continue;
			}
			ans++;
			vis[a[i]]++;
			q.push({a[i],vis[a[i]]});
			sum++;
			if(sum>k){
				node now=q.front();
				q.pop();
				while(now.val<vis[now.id]) {
					now=q.front();
					q.pop();
				}
				vis[now.id]=0;
			}
		}
		cout<<ans<<" ";
	}

	return 0;
}

