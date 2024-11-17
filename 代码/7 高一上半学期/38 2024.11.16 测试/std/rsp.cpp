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
const int N=2000+5,M=N*100+5,K=1e7+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const ll INF=5e18+7;mt19937 rnd(time(0));
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
int n,m,A[N];
ll f[N][N*2][3];
void Solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	ll ans=0;
	f[0][n][0]=f[0][n][1]=f[0][n][2]=1;
	for(int i=1;i<=n;i++){
		if(A[i]==-1) ans=ans*3%mod;
		for(int j=-n;j<=n;j++) for(int o:{0,1,2}) if(f[i-1][j+n][o]){
			for(int p:{0,1,2}) if(p==A[i]||A[i]==-1){
				int x,y;
				if(p==(o+1)%3) x=0,y=max(1,j+1);
				else if(p==o) x=j,y=1;
				else x=max(0,j),y=j+1;
				ans+=f[i-1][j+n][o]*x%mod;
				(f[i][y-x+n][p]+=f[i-1][j+n][o])%=mod;
			}
		}
	}
	for(int j=-n;j<=n;j++) for(int o:{0,1,2}) ans+=max(j,0)*f[n][j+n][o]%mod;
	printf("%lld\n",(ans%mod+mod)%mod*((mod+1)/3)%mod);
}
int main(){
	int t=1;
	// scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}