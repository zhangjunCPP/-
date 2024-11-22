#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10,INF=3e9;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
bool vis[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n;j++)vis[j]=false;
		priority_queue<int> q;
		int ans=0;
		q.push(-i);
		vis[i]=true;
		while(!q.empty()){
			int now=-q.top();q.pop();
			ans++;
			if(now==1)break;
			for(int j=first[now];j;j=a[j].nex){
				int v=a[j].v;
				if(!vis[v])q.push(-v),vis[v]=true;
			}
		}
		cout<<ans-1<<" ";
	}
}