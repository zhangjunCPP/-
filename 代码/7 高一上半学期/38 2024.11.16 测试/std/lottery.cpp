#include<bits/stdc++.h>
#define Gc() getchar()
#define Me(x,y) memset(x,y,sizeof(x))
#define Mc(x,y) memcpy(x,y,sizeof(x))
#define d(x,y) ((m)*(x-1)+(y))
#define R(n) (rnd()%(n)+1)
#define Pc(x) putchar(x)
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define eb emplace_back
#define all(x) x.begin(),x.end()
using namespace std;using ll=long long;using db=double;using lb=long db;using ui=unsigned;using ull=unsigned ll;using pii=pair<int,int>;
const int N=4e5+5,M=N*100+5,K=1e7+5,mod=1e9+7,Mod=mod-1;const db eps=1e-9;const ll INF=5e18+7;mt19937 rnd(time(0));
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
#ifdef LOCAL
#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
#else
#define gdb(...) void()
#endif
}using namespace Debug;
int n,m,k,lim;
ll frc[N],inv[N];
void init(){
	const int n=4e5;
	inv[1]=1;for(int i=2;i<=n;i++) inv[i]=(mod-inv[mod%i])*(mod/i)%mod;
	for(int i=frc[0]=inv[0]=1;i<=n;i++) frc[i]=frc[i-1]*i%mod,inv[i]=inv[i-1]*inv[i]%mod;
}
ll C(int x,int y){return x>=y&&y>=0?frc[x]*inv[y]%mod*inv[x-y]%mod:0;}
ll f[N];
ll calc(int x){
	return C(n+1+x+1,n+1+1);
}
void Solve(){
	scanf("%d%d%d",&n,&m,&k);
	lim=1ll*n*m/k;
	ll ans=0;
	for(int i=0;i*(3*i-1)/2<=lim;i++) ans+=(i&1?-1:1)*C(lim-i*(3*i-1)/2+n+1,n+1);
	for(int i=1;i*(3*i+1)/2<=lim;i++) ans+=(i&1?-1:1)*C(lim-i*(3*i+1)/2+n+1,n+1);
	for(int i=0;i*(3*i-1)/2<=n+1&&i*(3*i-1)/2+n+2<=lim;i++){
		int w=i*(3*i-1)/2;
		ans+=(i&1?-1:1)*calc(lim-w-(n+2));
	}
	for(int i=1;i*(3*i+1)/2<=n+1&&i*(3*i+1)/2+n+2<=lim;i++){
		int w=i*(3*i+1)/2;
		ans+=(i&1?-1:1)*calc(lim-w-(n+2));
	}
	ans=(ans%mod+mod)%mod;
	printf("%lld\n",(mod+1-ans%mod*inv[n+1]%mod)%mod);
}
int main(){
	init();
	int t=1;
	scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}