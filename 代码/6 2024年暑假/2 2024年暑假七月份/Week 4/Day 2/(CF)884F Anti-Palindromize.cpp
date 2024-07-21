#include<bits/stdc++.h>
const int MAX=1<<30;
using namespace std;
const int N=1e6+10;
struct node {
	int v,w,nex,val;
}a[N];
int first[N],cnt=1;
void add(int u,int v,int w,int val) {
	a[++cnt]=node{v,w,first[u],val};
	first[u]=cnt;
}
void add_edge(int u,int v,int w,int val) {add(u,v,w,val);add(v,u,0,-val);}
bool vis[N];
int now[N];
int dis[N];
bool spfa(int s,int t) {
	memset(dis,0x3f,sizeof dis);
	queue<int> q;
	q.push(s);
	dis[s]=0;
	vis[s]=true;
	now[s]=first[s];
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=first[u];i;i=a[i].nex) {
			if(a[i].w) {
				int v=a[i].v;
				if(dis[v]>dis[u]+a[i].val) {
					now[v]=first[v];
					dis[v]=dis[u]+a[i].val;
					if(!vis[v]) q.push(v),vis[v]=true;
				}
			}
		}
	}
	if(dis[t]==0x3f3f3f3f)return false;
	return true;
}
int dinic(int x,int val,int t) {
	if(x==t) return val;
	int have=val;
	vis[x]=true;
	for(int i=now[x];i&&have;i=a[i].nex) {
		now[x]=i;
		int v=a[i].v;
		if(!vis[v]&&a[i].w&&dis[v]==dis[x]+a[i].val) {
			int tmp=dinic(v,min(a[i].w,have),t);
			if(!tmp) dis[v]=0;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	vis[x]=false;
	return val-have;
}
int calc(int s,int t) {
	int ans=0;
	while(spfa(s,t)) {
		int tmp;
		while((tmp=dinic(s,MAX,t)))ans+=tmp*dis[t];
	}
	return ans;
}
int b[N];
int tot[N];
signed main() {
	int n;
	string s;
	cin>>n>>s;
	for(int i=0;i<n;i++)cin>>b[i];
	for(int i=0;i<n;i++)tot[s[i]-'a'+1]++;
	int S=0;
	for(int i=1;i<=26;i++)add_edge(S,i,tot[i],0);
	for(int i=1;i<=26;i++) {
		for(int j=1;j<=n/2;j++) {
			int Max=0;
			if(s[j-1]-'a'+1==i)Max=max(Max,b[j-1]);
			if(s[n-j]-'a'+1==i)Max=max(Max,b[n-j]);
			add_edge(i,j+26,1,-Max);
		}
	}
	int T=26+n/2+1;
	for(int i=1;i<=n/2;i++)add_edge(i+26,T,2,0);
	cout<< -calc(S,T);
}