#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int val,id;
	bool operator<(const node &b) const{
		return val>b.val;
	}
};
priority_queue<node> q;
int l[N],r[N];
int dis[N];

bool vis[N];
signed main(){
	int n,k;
	cin>>n>>k;

	int last;
	cin>>last;
	for(int i=1;i<n;i++){
		int x;
		cin>>x;
		dis[i]=x-last;
		q.push({dis[i],i});
		last=x;
		l[i]=i-1;
		r[i]=i+1;
	}
	dis[0]=dis[n]=0x3f3f3f3f;
	int ans=0;
	while(k--){
		while(vis[q.top().id]) q.pop();
		node now=q.top();
		q.pop();
		ans+=now.val;
		vis[l[now.id]]=vis[r[now.id]]=true;
		dis[now.id]=dis[l[now.id]]+dis[r[now.id]]-dis[now.id];
		q.push({dis[now.id],now.id});
		l[now.id]=l[l[now.id]];
		r[now.id]=r[r[now.id]];
		r[l[now.id]]=now.id;
		l[r[now.id]]=now.id;
	}
	cout<<ans;
	return 0;
}