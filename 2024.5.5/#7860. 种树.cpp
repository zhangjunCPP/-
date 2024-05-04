#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	#define pf printf
	#define pc putchar
	#define fr(i,a,b) for(ll i=(a);i<=(b);i++)
	#define pfr(i,a,b) for(ll i=(a);i>=(b);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define space pc(' ')
	#define enter pc('\n')
	#define il inline
	#define fir first
	#define sec second
	#define MP make_pair
	#define inf 8e18
	il ll read(){
		ll sum=0,fu=0;
		char ch=getchar();
		while(!isdigit(ch)){
			if(ch=='-') fu=1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch-'0');
			ch=getchar();
		}
		return fu?(-sum):sum;
	}
	void write(ll x){
		if(x<0){
			pc('-');
			x=-x;
		}
		if(x>9) write(x/10);
		pc('0'+x%10);
	}
	il void writesp(ll x){
		write(x);
		space;
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
}
using namespace my_std;
#define LC lc[x]
#define RC rc[x]
#define mod 1000000007
ll n,k,a[1000010],head[1000010],cnt=0,siz[1000010],f[1000010];
ll rt[1000010],tree[20000020],lc[20000020],rc[20000020],tot=0;
struct node{
	ll nxt,to;
}e[1000010];
void add(ll u,ll v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
il void pushup(ll x){
	tree[x]=tree[LC]+tree[RC];
}
void mdf(ll &x,ll l,ll r,ll pos){
	if(!x) x=++tot;
	if(l==r){
		tree[x]=1;
		return;
	}
	ll mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,l,mid,pos);
	else mdf(RC,mid+1,r,pos);
	pushup(x);
}
ll merge(ll x,ll y,ll l,ll r){
	if(!x) return y;
	if(!y) return x;
	if(l==r){
		tree[x]|=tree[y];
		return x;
	}
	ll mid=(l+r)>>1;
	LC=merge(LC,lc[y],l,mid);
	RC=merge(RC,rc[y],mid+1,r);
	pushup(x);
	return x;
}
void dfs(ll u){
	siz[u]=1;
	go(u){
		ll v=e[i].to;
		dfs(v);
		siz[u]+=siz[v];
		rt[u]=merge(rt[u],rt[v],1,k);
	}
	mdf(rt[u],1,k,a[u]);
	f[u]=tree[rt[u]];
}
il ll my_pow(ll x,ll y){
	ll res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int main(){
	n=read();
	k=read();
	fr(i,1,n) a[i]=read();
	fr(i,2,n){
		ll fa=read();
		add(fa,i);
	}
	dfs(1);
	ll ans=1;
	fr(i,2,n) if(f[i]*siz[ans]<f[ans]*siz[i]) ans=i;
	write(f[ans]*my_pow(siz[ans],mod-2)%mod);
}
