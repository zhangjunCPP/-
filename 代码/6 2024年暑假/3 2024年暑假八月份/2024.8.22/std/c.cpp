#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const ll N = 2e6+5,mod = 998244353;
ll n,m,q,L,idx,Lx,bx[N],b[N],id[N],len[N],mn[N*4],mx[N*4],val[N*4],mul[N*4],hp[N];
vector<int> vec[N],con[N];
struct Node{
	ll l,r,x;
}a[N];
ll qpow(ll a,ll p){
	ll res = 1;
	for(;p;p>>=1,a=a*a%mod) if(p&1) res = res*a%mod;
	return res;
}
void build(int l,int r,int u){
	mn[u] = m;
	if(l==r) return ;
	int mid = (l+r)>>1;
	build(l,mid,u*2),build(mid+1,r,u*2+1);
}
void cover(int l,int r,int u,int sl,int sr,ll x){
	if(sl>r || l>sr) return ;
	if(sl<=l && r<=sr){
		mn[u] = min(mn[u],x);
		return ;
	}
	int mid = (l+r)>>1;
	cover(l,mid,u*2,sl,sr,x),cover(mid+1,r,u*2+1,sl,sr,x);
}
void dfs(int l,int r,int u){
	if(l==r){
		mx[u] = mn[u];
		return ;
	}
	int mid = (l+r)>>1;
	mn[u*2] = min(mn[u*2],mn[u]);
	mn[u*2+1] = min(mn[u*2+1],mn[u]);
	dfs(l,mid,u*2),dfs(mid+1,r,u*2+1);
	mx[u] = max(mx[u*2],mx[u*2+1]);
}
ll ask(int l,int r,int u,int sl,int sr){
	if(sl>r || l>sr) return 0;
	if(sl<=l && r<=sr) return mx[u];
	int mid = (l+r)>>1;
	return max(ask(l,mid,u*2,sl,sr),ask(mid+1,r,u*2+1,sl,sr));
}
void add(int u,ll w){
	mul[u] = mul[u]*w%mod,val[u] = val[u]*w%mod;
}
void pushdown(int u){
	if(mul[u]!=1){
		add(u*2,mul[u]),add(u*2+1,mul[u]);
		mul[u] = 1;
	}
}
void clear(int l,int r,int u){
	val[u] = 0,mul[u] = 1;
	if(l==r) return ;
	int mid = (l+r)>>1;
	clear(l,mid,u*2),clear(mid+1,r,u*2+1);
}
void chg(int l,int r,int u,int p,ll w){
	if(l==r){
		val[u] = w;
		return ;
	}
	pushdown(u);
	int mid = (l+r)>>1;
	if(p<=mid) chg(l,mid,u*2,p,w);
	else chg(mid+1,r,u*2+1,p,w);
	val[u] = (val[u*2]+val[u*2+1])%mod;
}
void upd(int l,int r,int u,int sl,int sr,ll w){
	if(sl>r || l>sr) return ;
	if(sl<=l && r<=sr){
		add(u,w);
		return ;
	}
	int mid = (l+r)>>1;
	pushdown(u);
	upd(l,mid,u*2,sl,sr,w),upd(mid+1,r,u*2+1,sl,sr,w);
	val[u] = (val[u*2]+val[u*2+1])%mod;
}
ll qry(int l,int r,int u,int sl,int sr){
	if(sl>r || l>sr) return 0;
	if(sl<=l && r<=sr) return val[u];
	int mid = (l+r)>>1;
	pushdown(u);
	return (qry(l,mid,u*2,sl,sr)+qry(mid+1,r,u*2+1,sl,sr))%mod;
}
ll solve(ll w){
	ll siz = vec[w].size(),x = bx[w];
	for(int i=0;i<=siz;i++) hp[i] = 0;
	for(int i:con[w]){
		ll l = lower_bound(vec[w].begin(),vec[w].end(),a[i].l)-vec[w].begin(),r = upper_bound(vec[w].begin(),vec[w].end(),a[i].r)-vec[w].begin();r--;
		hp[r+1] = max(hp[r+1],l+1);
	}
	clear(0,siz,1);chg(0,siz,1,0,1);
	for(int i=1;i<=siz;i++){
		ll y = qry(0,siz,1,0,i-1)*(qpow(x,len[vec[w][i-1]])-qpow(x-1,len[vec[w][i-1]])+mod)%mod;
		chg(0,siz,1,i,y);
		upd(0,siz,1,0,i-1,qpow(x-1,len[vec[w][i-1]]));
		if(hp[i]) upd(0,siz,1,0,hp[i]-1,0);
	}
	return qry(0,siz,1,0,siz);
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	int T;cin >> T;
	while(T--){
		cin >> n >> q >> m;
		Lx = L = idx = 0;
		bx[++Lx] = m;
		for(int i=1;i<=q;i++){
			cin >> a[i].l >> a[i].r >> a[i].x;
			b[++L] = a[i].l,b[++L] = a[i].r,bx[++Lx] = a[i].x;
		}
		sort(b+1,b+1+L),sort(bx+1,bx+1+Lx);
		L = unique(b+1,b+1+L)-b-1,Lx = unique(bx+1,bx+1+Lx)-bx-1;
		b[++L] = n+1;
		for(int i=1;i<=L;i++){
			if(b[i]-b[i-1]>1) len[++idx] = b[i]-b[i-1]-1;
			if(i!=L) len[++idx] = 1,id[i] = idx;
		}
		n = idx;build(1,n,1);
		for(int i=1;i<=Lx;i++) con[i].clear(),vec[i].clear();
		for(int i=1;i<=q;i++){
			int l = id[lower_bound(b+1,b+1+L,a[i].l)-b],r = id[lower_bound(b+1,b+1+L,a[i].r)-b],x = a[i].x;
			cover(1,n,1,l,r,x);
			a[i].l = l,a[i].r = r;
			x = lower_bound(bx+1,bx+1+Lx,a[i].x)-bx,con[x].pb(i);
		}
		dfs(1,n,1);
		int ck = 0;
		for(int i=1;i<=q;i++){
			if(ask(1,n,1,a[i].l,a[i].r)<a[i].x){
				cout << 0 << '\n';
				ck = 1;
				break;
			}
		}
		if(ck) continue;
		for(int i=1;i<=n;i++){
			int u = lower_bound(bx+1,bx+1+Lx,ask(1,n,1,i,i))-bx;
			vec[u].pb(i);
		}
		ll ans = 1;
		for(int i=1;i<=Lx;i++) if(vec[i].size()) ans = ans*solve(i)%mod;
		cout << ans << '\n';
	}
	return 0;
}