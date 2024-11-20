#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=3e6+10;
const ll INF=1e18;
int n;
struct node{
	int v;
	ll w;
	int nex;
}a[N];
int first[N],cnt;
void add(int u,int v,ll w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
ll dis[N];
bool vis[N];
void spfa(int s){
	queue<int> q;
	for(int i=1;i<=n;i++)dis[i]=INF,vis[i]=false;
	dis[s]=0;
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				if(!vis[v])q.push(v),vis[v]=true;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n-1;i++){
		ll x;
		cin>>x;
		add(i,i+1,x);
	}
	for(int i=1;i<=n-2;i++){
		ll x;
		cin>>x;
		add(i,i+2,x);
	}
	for(int i=1;i<=n-3;i++){
		ll x;
		cin>>x;
		add(i,i+3,x);
	}
	ll ans=0;
	for(int i=1;i<n;i++){
		spfa(i);
		for(int j=i+1;j<=n;j++)ans+=dis[j];
	}
	cout<<ans;
}