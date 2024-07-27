#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	ll my_pow(ll a,ll b,ll mod){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res=(res*a)%mod;
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	ll qpow(ll a,ll b){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	#define db double
	#define pf printf
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define enter pc('\n')
	#define space pc(' ')
	#define fir first
	#define sec second
	#define MP make_pair
	#define il inline
	#define inf 8e18
	#define random(x) rand()*rand()%(x)
	#define inv(a,mod) my_pow((a),(mod-2),(mod))
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
	il void writesp(ll x){
		write(x);
		space;
	}
}
using namespace my_std;
#define LC lc[x]
#define RC rc[x]
vector<ll> vec[100010];
ll n,m,rt[100010],lc[2000020],rc[2000020],tot=0;
ll f[100010],lim[100010],q[100010];
struct node{
	ll v,vl,vr;
}tree[2000020];
il node operator+(const node &x,const node &y){
	return (node){x.v+y.v,x.vl+y.vl,x.vr+y.vr};
}
il node operator-(const node &x,const node &y){
	return (node){x.v-y.v,x.vl-y.vl,x.vr-y.vr};
}
il void pushup(ll x){
	tree[x]=tree[LC]+tree[RC];
}
il void mdf(ll &x,ll y,ll l,ll r,ll pos,node v){
	x=++tot;
	tree[x]=tree[y]+v;
	LC=lc[y];
	RC=rc[y];
	if(l==r) return;
	ll mid=(l+r)>>1;
	if(pos<=mid) mdf(LC,lc[y],l,mid,pos,v);
	else mdf(RC,rc[y],mid+1,r,pos,v);
	pushup(x);
}
node query(ll x,ll y,ll l,ll r,ll ql,ll qr){
	if(ql<=l&&r<=qr) return tree[x]-tree[y];
	ll mid=(l+r)>>1;
	node res=(node){0,0,0};
	if(ql<=mid) res=res+query(LC,lc[y],l,mid,ql,qr);
	if(mid<qr) res=res+query(RC,rc[y],mid+1,r,ql,qr);
	return res;
}
il node calc(ll xl,ll xr,ll yl,ll yr){
	xl=max(xl,1ll);
	xr=min(xr,n);
	yl=max(yl,1ll);
	yr=min(yr,n);
	if(xl>xr||yl>yr) return (node){0,0,0};
	return query(rt[xr],rt[xl-1],1,n,yl,yr);
}
il ll solve(ll l,ll r){
	l=max(l,1ll);
	r=min(r,n);
	if(l>=r) return 0;
	ll mid=(l+r)>>1,ans=0;
	node res=calc(l,r,l,r);
	ans+=(r-l)*res.v+res.vl-res.vr;
	res=calc(1,l,r,n);
	ans+=res.v;
	res=calc(1,l-1,l,mid);
	ans+=res.vr-l*res.v;
	res=calc(1,l-1,mid+1,r);
	ans+=r*res.v-res.vr;
	res=calc(l,mid,r+1,n);
	ans+=res.vl-l*res.v;
	res=calc(mid+1,r,r+1,n);
	ans+=r*res.v-res.vl;
	return ans;
}
int main(){
	freopen("block.in", "r", stdin);
	freopen("block.out", "w", stdout);
	n=read();
	m=read();
	fr(i,1,m){
		ll l=read(),r=read();
		vec[l].push_back(r);
	}
	fr(i,1,n){
		rt[i]=rt[i-1];
		fr(j,0,(ll)vec[i].size()-1) mdf(rt[i],rt[i],1,n,vec[i][j],(node){1,i,vec[i][j]});
	}
	ll l=1,r=0;
	q[++r]=0;
	lim[0]=1;
	fr(i,1,n){
		while(l<r&&lim[q[l+1]]<=i) l++;
		f[i]=f[q[l]]+solve(q[l],i);
		if(i==n) break;
		while(l<=r&&lim[q[r]]>i&&(f[q[r]]+solve(q[r],lim[q[r]]))>=(f[i]+solve(i,lim[q[r]]))) r--;
		ll L=max(lim[q[r]]+1,i+1),R=n+1;
		while(L<R){
			ll mid=(L+R)>>1;
			if((f[q[r]]+solve(q[r],mid))>=(f[i]+solve(i,mid))) R=mid;
			else L=mid+1;
		}
		lim[i]=L;
		q[++r]=i;
	}
	write(f[n]);
}
