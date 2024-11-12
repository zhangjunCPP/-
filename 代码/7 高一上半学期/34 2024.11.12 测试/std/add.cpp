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
using namespace std;using ll=long long;using db=double;using lb=long db;using ui=unsigned;using ull=unsigned long long;using pii=pair<int,int>;
const int N=3e5+5,M=N*N+5,K=1e7+5,mod=1e9+7,Mod=mod-1;const db eps=1e-9;const int INF=1e9+7;mt19937 rnd(time(0));
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
int q;
ll a[N],b[N];
ll ans[N];
void Solve(){
	scanf("%d",&q);
	for(int i=1;i<=q;i++) scanf("%lld%lld",&a[i],&b[i]),ans[i]=0;
	for(int i=0;i<32;i++){
		for(int j=1;j<=q;j++){
			ans[j]|=(((a[j]^ans[j-1])+(b[j]^ans[j-1]))>>i&1)<<i;
		}
		ans[0]=ans[q];
	}
	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
int main(){
	int t=1;
	// scanf("%d",&t);
	while(t--) Solve();
}