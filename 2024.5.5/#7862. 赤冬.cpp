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
ll n,a[200020],head[200020],cnt=0;
ll all,siz[200020],f[200020],ans=0;
ll b[55],tot=0,c1[300030],c2[300030];
struct node{
	ll nxt,to;
}e[400040];
void add(ll u,ll v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
void dfs1(ll fa,ll u){
	siz[u]=a[u];
	go(u){
		ll v=e[i].to;
		if(v==fa) continue;
		dfs1(u,v);
		siz[u]+=siz[v];
		f[u]+=f[v]+a[u]*siz[v];
	}
}
il ll solve(){
	ll len1=tot/2,len2=tot-len1,cnt1=0,cnt2=0;
	fr(i,0,(1ll<<len1)-1){
		ll tmp=0;
		fr(j,1,len1) if(i&(1ll<<(j-1))) tmp+=b[j];
		c1[++cnt1]=tmp;
	}
	fr(i,0,(1ll<<len2)-1){
		ll tmp=0;
		fr(j,1,len2) if(i&(1ll<<(j-1))) tmp+=b[len1+j];
		c2[++cnt2]=tmp;
	}
	sort(c1+1,c1+cnt1+1);
	sort(c2+1,c2+cnt2+1);
	ll sum=0,now=cnt2,res=0;
	fr(i,1,tot) sum+=b[i];
	fr(i,1,cnt1){
		while(now>=1&&(c1[i]+c2[now])>sum/2) now--;
		if(!now) break;
		res=max(res,c1[i]+c2[now]);
	}
	return res;
}
void dfs2(ll fa,ll u){
	ll sum=0,maxx=0,now=0;
	go(u){
		ll v=e[i].to;
		sum+=f[v];
		maxx=max(maxx,siz[v]);
		now+=siz[v];
	}
	sum+=a[u]*(all-a[u]);
	if(maxx>=(now+1)/2) ans=max(ans,sum+maxx*(now-maxx));
	else{
		tot=0;
		go(u){
			ll v=e[i].to;
			b[++tot]=siz[v];
		}
		ll tmp=solve();
		ans=max(ans,sum+tmp*(now-tmp));
	}
	go(u){
		ll v=e[i].to;
		if(v==fa) continue;
		f[u]-=a[u]*siz[v]+f[v];
		siz[u]-=siz[v];
		siz[v]+=siz[u];
		f[v]+=a[v]*siz[u]+f[u];
		dfs2(u,v);
		f[v]-=a[v]*siz[u]+f[u];
		siz[v]-=siz[u];
		siz[u]+=siz[v];
		f[u]+=a[u]*siz[v]+f[v];
	}
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("wa.out","w",stdout);
	n=read();
	fr(i,1,n) a[i]=read();
	fr(i,2,n){
		ll fa=read();
		add(fa,i);
		add(i,fa);
	}
	dfs1(0,1);
	all=siz[1];
	dfs2(0,1);
	fr(i,1,n) ans+=a[i]*(a[i]-1);
	write(ans);
}
/*
6
3 3 3 1 2 1 
1 2 1 2 2 
ans:
78
*/
