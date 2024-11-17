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
const int N=1e6+5,M=N*100+5,K=1e7+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const ll INF=5e18+7;mt19937 rnd(time(0));
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
ll n;
void Solve(){
	scanf("%lld",&n);
	ll y=sqrtl(n);
	ll ans=INF;
	for(int i=max(1ll,y-10);i<=y+10;i++){
		if(~i&1){
			if(~n&1) ans=min(ans,i+1+(n+i-1)/i);
		}else{
			ll z=(n+i-1)/i;
			ans=min(ans,i+1+z+((z&1)!=(n&1)));
		}
	}
	printf("%lld\n",ans);
}
int main(){
	int t=1;
	scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}