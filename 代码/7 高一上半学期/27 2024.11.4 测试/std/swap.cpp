#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define pc __builtin_popcount
#define pcl __builtin_popcountll
#define lb(x) ((x)&-(x))
using namespace std;
const ll P=998244353;
ll qpow(ll x,ll y=P-2){ll z=1;while(y){if(y&1)z=z*x%P;x=x*x%P,y>>=1;}return z;}

const int N=2e5+5,M=N*23;
vector<int> e[M];int tot=0;
void add(int x,int y){e[x].pb(y);}
int id[M];
int deg[M];vector<int> ans;bool vis[M];
struct cmp{bool operator()(int x,int y){return id[x]>id[y];}};
void solve(){
	for(int i=1;i<=tot;i++) for(int j:e[i]) deg[j]++;
	priority_queue<int,vector<int>,cmp> q;
	for(int i=1;i<=tot;i++) if(!deg[i]) q.push(i);
	while(!q.empty()){
		int x=q.top();q.pop();
		if(vis[x]) continue;;vis[x]=1,ans.pb(id[x]);
		for(int i:e[x]){deg[i]--;if(!deg[i]) q.push(i);}
	}
}

int n,a[N],b[N];
int v[N*2];
#define _add(x,y) add(y,x)
void work(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	vector<pii> q;vector<int> u;
	int i;
	for(i=l;i<=mid;i++) if(v[i]) q.pb({v[i],i});
	if(!q.size()) goto E;
	sort(q.begin(),q.end());
	for(i=0;i<(int)q.size();i++) u.pb(++tot);
	for(i=1;i<(int)q.size();i++){
		_add(u[i],u[i-1]);
		_add(u[i],q[i].se);
	}_add(u[0],q[0].se);
	for(i=mid+1;i<=r;i++) if(v[i]){
		int x=lower_bound(q.begin(),q.end(),make_pair(v[i],0))-q.begin()-1;
		if(x>=0) _add(i,u[x]);
	}E:
	work(l,mid),work(mid+1,r);
}
int ___[N];
int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int i,x;
	cin>>n;
	for(i=1;i<=n+n;i++){
		cin>>x;___[x]++;if(a[x]) b[x]=i;else a[x]=i;
	}
	for(i=1;i<=n;i++) assert(___[i]==2);
	tot=2*n;for(i=1;i<=n;i++) id[a[i]]=i;
	for(i=1;i<=n;i++) v[a[i]]=b[i];
	work(1,2*n);
	solve();
	for(int i:ans) if(i) cout<<i<<' '<<i<<' ';
	return 0;
}