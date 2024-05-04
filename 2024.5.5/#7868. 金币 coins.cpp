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
	#define inf 1e18
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
ll t,typ,n,a,b,lft[100010],rgt[100010];
char s[100010],ss[100010];
struct node{
	ll maxx,now,lst;
}pre[100010][2],suf[100010][2];
il void chkmax(node &x,node v){
	if(x.maxx<v.maxx||(x.maxx==v.maxx&&x.now>v.now)) x=v;
}
il bl solve(ll k){
	fr(i,1,n) s[i]=ss[i];
	fr(i,1,n){
		if(i>1&&s[i]=='?'&&s[i-1]!='?'&&lft[i-1]==k) s[i]=s[i-1]^1;
		if(s[i]=='?') continue;
		if(i>1&&s[i]==s[i-1]) lft[i]=lft[i-1]+1;
		else lft[i]=1;
		if(lft[i]>k) return 0;
	}
	pfr(i,n,1){
		if(i<n&&s[i]=='?'&&s[i+1]!='?'&&rgt[i+1]==k) s[i]=s[i+1]^1;
		if(s[i]=='?') continue;
		if(i>1&&s[i]==s[i+1]) rgt[i]=rgt[i+1]+1;
		else rgt[i]=1;
		if(rgt[i]>k) return 0;
	}
	fr(i,1,n) fr(j,0,1) pre[i][j]=suf[i][j]=(node){-(ll)inf,0,0};
	pre[0][0]=pre[0][1]=suf[n+1][0]=suf[n+1][1]=(node){0,0,0};
	fr(i,1,n){
		if(s[i]!='1'){
			if(pre[i-1][0].maxx>=0&&pre[i-1][0].now!=k) chkmax(pre[i][0],(node){pre[i-1][0].maxx+1,pre[i-1][0].now+1,0});
			if(pre[i-1][1].maxx>=0) chkmax(pre[i][0],(node){pre[i-1][1].maxx+1,1,1});
		}
		if(s[i]!='0'){
			if(pre[i-1][0].maxx>=0) chkmax(pre[i][1],(node){pre[i-1][0].maxx,1,0});
			if(pre[i-1][1].maxx>=0&&pre[i-1][1].now!=k) chkmax(pre[i][1],(node){pre[i-1][1].maxx,pre[i-1][1].now+1,1});
		}
		if(i<n&&s[i]=='?'&&s[i+1]!='?'){
			if(s[i+1]=='0'&&(pre[i][0].now+rgt[i+1])>k) pre[i][0].maxx=-inf;
			if(s[i+1]=='1'&&(pre[i][1].now+rgt[i+1])>k) pre[i][1].maxx=-inf;
		}
		if(pre[i][0].maxx<0&&pre[i][1].maxx<0) return 0;
	}
	pfr(i,n,1){
		if(s[i]!='1'){
			if(suf[i+1][0].maxx>=0&&suf[i+1][0].now!=k) chkmax(suf[i][0],(node){suf[i+1][0].maxx,suf[i+1][0].now+1,0});
			if(suf[i+1][1].maxx>=0) chkmax(suf[i][0],(node){suf[i+1][1].maxx,1,1});
		}
		if(s[i]!='0'){
			if(suf[i+1][0].maxx>=0) chkmax(suf[i][1],(node){suf[i+1][0].maxx+1,1,0});
			if(suf[i+1][1].maxx>=0&&suf[i+1][1].now!=k) chkmax(suf[i][1],(node){suf[i+1][1].maxx+1,suf[i+1][1].now+1,1});
		}
		if(i>1&&s[i]=='?'&&s[i-1]!='?'){
			if(s[i-1]=='0'&&(suf[i][0].now+lft[i-1])>k) suf[i][0].maxx=-inf;
			if(s[i-1]=='1'&&(suf[i][1].now+lft[i-1])>k) suf[i][1].maxx=-inf;
		}
		if(suf[i][0].maxx<0&&suf[i][1].maxx<0) return 0;
	}
	return max(pre[n][0].maxx,pre[n][1].maxx)>=a&&max(suf[1][0].maxx,suf[1][1].maxx)>=b;
}
il void chkr(){
	fr(i,1,n) if(s[i]!='0'&&s[i]!='1') assert(0);
	fr(i,1,n) if(ss[i]!='?'&&s[i]!=ss[i]) assert(0);
	ll tmp1=0,tmp2=0;
	fr(i,1,n) if(s[i]=='0') tmp1++;
	fr(i,1,n) if(s[i]=='1') tmp2++;
	assert(a==tmp1&&b==tmp2);
}
int main(){
	t=read();
	typ=read();
	while(t--){
		n=read();
		a=read();
		b=read();
		scanf("%s",s+1);
		fr(i,1,n) if(s[i]=='0') a++;
		fr(i,1,n) if(s[i]=='1') b++;
		fr(i,1,n) ss[i]=s[i];
		ll l=1,r=n;
		while(l<r){
			ll mid=(l+r)>>1;
			if(solve(mid)) r=mid;
			else l=mid+1;
		}
		writeln(l);
		if(!typ) continue;
		solve(l);
		ll pos=0;
		fr(i,0,n) if(pre[i][0].maxx>=0&&suf[i+1][1].maxx>=0&&(i-pre[i][0].maxx+suf[i+1][1].maxx)==b) pos=i;
//		assert(pre[pos][0].maxx>=0&&suf[pos+1][1].maxx>=0&&(pos-pre[pos][0].maxx+suf[pos+1][1].maxx)==b);
		ll now=0;
		pfr(i,pos,1){
			s[i]='0'+now;
			now=pre[i][now].lst;
		}
		now=1;
		fr(i,pos+1,n){
			s[i]='0'+now;
			now=suf[i][now].lst;
		}
		fr(i,1,n) pc(s[i]);
		enter;
//		chkr();
	}
}
