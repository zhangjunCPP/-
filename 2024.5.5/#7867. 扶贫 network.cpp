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
ll n,a[1000010],L[1000010],R[1000010],st[1000010],top=0,id[1000010];
ll maxdep[1000010],f[1000010];
il bl cmp(ll x,ll y){
	return a[x]>a[y];
}
void dfs(ll u){
	if(L[u]) dfs(L[u]);
	if(R[u]) dfs(R[u]);
	maxdep[u]=max(maxdep[L[u]],maxdep[R[u]])+1;
	f[u]=maxdep[L[u]]+maxdep[R[u]]+2;
	if(L[u]) f[u]=max(f[u],f[L[u]]+1);
	if(R[u]) f[u]=max(f[u],f[R[u]]+1);
}
int main(){
//	freopen("network.in","r",stdin);
//	freopen("network.out","w",stdout);
	n=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n){
		ll tmp=top;
		while(top&&a[st[top]]<a[i]) top--;
		if(top<tmp) L[i]=st[top+1];
		if(top) R[st[top]]=i;
		st[++top]=i;
	}
	maxdep[0]=-1;
	dfs(st[1]);
	write(f[st[1]]);
}
