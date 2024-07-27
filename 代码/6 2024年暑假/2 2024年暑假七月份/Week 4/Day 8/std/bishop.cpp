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
vector<pair<ll,ll> > vec;
ll n,m;
int main(){
	freopen("bishop.in", "r", stdin);
	freopen("bishop.out", "w", stdout);
	n=read();
	m=read();
	bl swp=0;
	if(n<m){
		swap(n,m);
		swp=1;
	}
	if(n==m){
		writeln(max(1ll,2*n-2));
		fr(i,1,m) pf("1 %lld\n",i);
		fr(i,2,m-1) pf("%lld %lld\n",n,i);
		return 0;
	}
	fr(i,1,m) vec.push_back(MP(1,i));
	fr(i,1,m) vec.push_back(MP(n,i));
	if(m&1){
		fr(i,m/2+2,n-m/2-1) vec.push_back(MP(i,m/2+1));
	}
	else{
		for(ll i=m/2+2;i<=(n-m/2-1);i+=2){
			vec.push_back(MP(i,m/2));
			vec.push_back(MP(i,m/2+1));
		}
	}
	writeln((ll)vec.size());
	fr(i,0,(ll)vec.size()-1){
		if(swp) swap(vec[i].fir,vec[i].sec);
		pf("%lld %lld\n",vec[i].fir,vec[i].sec);
	}
}
