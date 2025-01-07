#include <bits/stdc++.h>

using namespace std;
const int N=3e6+10;

struct node1{
	int v,nex;
}a1[N];
int first1[N],cnt1;
void add1(int u,int v){
	a1[++cnt1]={v,first1[u]};
	first1[u]=cnt1;
}
struct node2{
	int v,nex;
}a2[N];
int first2[N],cnt2;
void add2(int u,int v){
	a2[++cnt2]={v,first2[u]};
	first2[u]=cnt2;
}

int dfn[N],low[N],idx;
stack<int> s;
int scc[N],tot;
bool vis[N];
void tarjan(int u){
	dfn[u]=low[u]=++idx;
	s.push(u);
	vis[u]=true;
	for(int i=first1[u];i;i=a1[i].nex){
		int v=a1[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		++tot;
		while (s.top()!=u){
			scc[s.top()]=tot;
			vis[s.top()]=false;
			s.pop();
		}
		scc[s.top()]=tot;
		vis[s.top()]=false;
		s.pop();
	}
}

map<pair<int,int>,int> mp;
int xx[N],yy[N];
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};

int val[N];
int dp[N];
int in[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);

	int n,r,c;
	cin>>n>>r>>c;
	for(int i=1;i<=n;i++) {
		int x,y,t;
		cin>>x>>y>>t;
		add1(x,r+c+i);
		add1(y+r,r+c+i);
		if(t==1) add1(r+c+i,x);
		if(t==2) add1(r+c+i,y+r);
		if(t==3){
			xx[i]=x;
			yy[i]=y;
		}
		mp[make_pair(x,y)]=i;
	}

	for(int i=1;i<=n;i++){
		if(xx[i]) {
			for (int j = 0; j < 8; j++)
				if (mp[make_pair(xx[i] + dx[j], yy[i] + dy[j])])
					add1(r+c+i,mp[make_pair(xx[i] + dx[j], yy[i] + dy[j])] + r + c);
		}
	}

	for(int i=1;i<=n+r+c;i++){
		if(!dfn[i]) tarjan(i);
	}

	for(int i=1;i<=n;i++)val[scc[i+r+c]]++;
	for(int i=1;i<=r+c+n;i++){
		for(int tmp=first1[i];tmp;tmp=a1[tmp].nex){
			int j=a1[tmp].v;
			if(scc[i]!=scc[j]){
				add2(scc[i],scc[j]);
				in[scc[j]]++;
			}
		}
	}
	queue<int> q;
	for(int i=1;i<=tot;i++){
		if(!in[i]){
			q.push(i);
			dp[i]=val[i];
		}
	}
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=first2[now];i;i=a2[i].nex){
			int v=a2[i].v;
			dp[v]=max(dp[v],dp[now]+val[v]);
			in[v]--;
			if(!in[v]) q.push(v);
		}
	}
	int ans=-1;
	for(int i=1;i<=tot;i++) ans=max(ans,dp[i]);
	cout<<ans;
}