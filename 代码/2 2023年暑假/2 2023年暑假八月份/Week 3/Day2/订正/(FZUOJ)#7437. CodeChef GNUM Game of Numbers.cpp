#include <bits/stdc++.h>
#define int long long
const int MAX=1ll<<40;
using namespace std;
const int N=1e7+10;
int s,t;
struct Node{
	int v,w,nex;
}a[N];
int cnt=1,first[N];
void add(int u,int v,int w){
	a[++cnt]=Node{v,w,first[u]};
	first[u]=cnt;
}
void insert(int u,int v,int w){
	add(u,v,w),add(v,u,0);
}
int now[N];
int d[N];
int bfs(){
	memset(d, false,sizeof d);
	queue<int> q;
	q.push(s);
	d[s]=1;
	now[s]=first[s];
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(a[i].w&&!d[v]){
				q.push(v);
				now[v]=first[v];
				d[v]=d[u]+1;
				if(v==t) return 1;
			}
		}
	}
	return 0;
}
int dinic(int x,int val){
	if(x==t) return val;
	int have=val;
	for(int i=now[x];i&&have;i=a[i].nex){
		now[x]=i;
		int v=a[i].v;
		if(a[i].w&&d[v]==d[x]+1){
			int tmp= dinic(v,min(a[i].w,have));
			if(!tmp) d[v]=0;
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			have-=tmp;
		}
	}
	return val-have;
}


int A[N],B[N];
vector<int> calc(int x){
	vector<int> tmp;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			tmp.push_back(i);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) tmp.push_back(x);
	return tmp;
}
void init(){
	cnt=1;
	memset(first,0,sizeof first);
}
void solve(){
	init();
	set<int> sa;
	map<int,int> sb;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>A[i];
	for(int i=1;i<=n;i++)cin>>B[i];
	for(int i=1;i<=n;i++){
		vector<int> tmp=calc(A[i]);
		for(int j:tmp) sa.insert(j);
	}
	int tot=0;
	for(int i=1;i<=n;i++){
		vector<int> tmp=calc(B[i]);
		for(int j:tmp) if(sa.count(j)&&!sb.count(j)) sb[j]=++tot;
	}
	s=++tot;t=++tot;
	for(int i=1;i<=n;i++){
		vector<int> tmp=calc(A[i]);
		for(int j=1;j<=n;j++){
			if(__gcd(A[i],B[j])>1&&A[i]!=B[j]){
				int now=++tot;
				if(A[i]>B[j]) insert(s,now,1);
				else insert(now,t,1);
				for(int k:tmp){
					if(B[j]%k==0){
						if(A[i]>B[j]) insert(now,sb[k],1);
						else insert(sb[k],now,1);
					}
				}
			}
		}
	}
	int ans=0;
	while(bfs()){
		int tmp;
		while (tmp=dinic(s,MAX)) ans+=tmp;
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--) solve();
}