#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=1e5+5, mo=1e18+7;

ll ans=0;
ll a[maxn], l[maxn], r[maxn], bl[maxn], ed[maxn], v[maxn], cnt[maxn], s[maxn], t[maxn], res[maxn];
mt19937 rnd(time(0));

void file(){
	freopen("dragon.in","r",stdin);
	freopen("dragon.out","w",stdout);
}


struct node {
	ll l;
	ll r;
	ll id;
}e[maxn];

bool cmp(node x,node y) {
	if(bl[x.l]!=bl[y.l]) return bl[x.l]<bl[y.l];
	return bl[x.r]<bl[y.r];
}

void add(ll x) {
	ans+=cnt[s[x]];
	cnt[s[x]]++;
	return ;
}

void sub(ll x) {
	cnt[s[x]]--;
	ans-=cnt[s[x]];
	return ;
}

int main() {
	file();
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	ll n,k,q; cin>>n>>k>>q;
	for(ll i=1;i<=n;i++) cin>>a[i], v[i]=rnd();
	for(ll i=1;i<=n;i++) {
		cnt[a[i]]=(cnt[a[i]]+1)%k;
		if(cnt[a[i]]) s[i]=(s[i-1]+v[a[i]])%mo;
		else s[i]=(s[i-1]-(__int128) (k-1)*v[a[i]]%mo+mo)%mo;
	}
	ll tot=0;
	t[++tot]=0;
	for(ll i=1;i<=n;i++) t[++tot]=s[i];
	sort(t+1,t+tot+1); unique(t+1,t+tot+1)-t-1;
	for(ll i=0;i<=n;i++) s[i]=lower_bound(t+1,t+tot+1,s[i])-t;
	ll len=sqrt(n);
	for(ll i=1;i<=n;i++) bl[i]=(i-1)/len+1;
	for(ll i=1;i<=q;i++) cin>>e[i].l>>e[i].r, e[i].id=i;
	sort(e+1,e+q+1,cmp);
	ll l=1, r=0;
	memset(cnt,0,sizeof(cnt));
	for(ll i=1;i<=q;i++) {
		while(r<=e[i].r) add(++r);
		while(l>=e[i].l) add(--l);
		while(r>e[i].r) sub(r--);
		while(l<e[i].l) sub(l++);
		res[e[i].id]=ans+cnt[s[e[i].l-1]];
	}
	for(ll i=1;i<=q;i++) cout<<res[i]<<'\n';
	return 0;
}
