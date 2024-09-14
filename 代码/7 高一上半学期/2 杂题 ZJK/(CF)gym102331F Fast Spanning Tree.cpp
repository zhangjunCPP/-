#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m;
struct node {
	int a,b,s;
}a[N];
int fa[N];
int find(int x) {
	if(fa[x]!=x)return fa[x]=find(fa[x]);
	return fa[x];
}
int siz[N];
priority_queue<pair<int,int>>q[N];
priority_queue<int>q2;
void insert(int id) {
	int u=find(a[id].a),v=find(a[id].b);
	if(u==v)return;
	if(siz[u]+siz[v]>=a[id].s) {
		q2.push(-id);
		return;
	}
	int tmp=(a[id].s-siz[u]-siz[v]+1)/2;
	q[u].push({-(siz[u]+tmp),id});
	q[v].push({-(siz[v]+tmp),id});
}
vector<int> ans;
void merge(int id) {
	int u=find(a[id].a),v=find(a[id].b);
	if(u==v)return;
	ans.push_back(id);
	if(q[u].size()>q[v].size())swap(u,v);
	fa[u]=v;
	siz[v]+=siz[u];
	while(!q[u].empty()) {
		auto it=q[u].top();
		q[u].pop();
		if(-it.first<=siz[v])insert(it.second);
		else q[v].push(it);
	}
	while(!q[v].empty()) {
		auto it=q[v].top();
		q[v].pop();
		if(-it.first<=siz[v])insert(it.second);
		else {
			q[v].push(it);
			return;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>siz[i];
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++) {
		cin>>a[i].a>>a[i].b>>a[i].s;
		insert(i);
	}
	while(!q2.empty()) {
		int id=-q2.top();
		q2.pop();
		merge(id);
	}
	cout<<ans.size()<<"\n";
	for(int it:ans)cout<<it<<" ";
}