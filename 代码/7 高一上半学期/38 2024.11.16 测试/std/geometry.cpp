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
const int N=50+5,M=N*4+5,K=1000+5,mod=998244353,Mod=mod-1;const db eps=1e-8;const int INF=1e9+7;mt19937 rnd(263082);
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
int n,m,k,A[N][N],B[N],id[N];
vector<tuple<int,int,int,int>> ans;
void add(int x,int y,int z,int w){
	ans.emplace_back(x,y,z,w);
}
void Solve(){
	int i,j,h;scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++) scanf("%d",&A[i][j]),B[A[i][j]]++;
	iota(id+1,id+k+1,1);sort(id+1,id+k+1,[](int x,int y){return B[x]>B[y];});
	for(j=1;j<=m;j++){
		for(i=1;i<=n;i++){
			for(h=2;h<=m-j+1;h++) add(i,j,h,A[i][j]);
			for(h=j+1;h<=2*j;h++) add(i,h,m-j+1,A[i][j]);
			for(h=m-j+2;h<=m;h++) add(i,2*j,h,A[i][j]);
		}
	}
	for(i=1;i<=k;i++){
		int z=id[i];
		for(int x=1;x<=n;x++) for(int y=1;y<=m+1;y+=2) add(x,2*y-1,m+i,z);
		for(int y=1;y<=2*m+2;y++) add(n+1,y,m+i,z);
		for(int x=1;x<=n;x++) for(int y=1;y<=m;y++)if(A[x][y]==z){
			for(j=m+1;j<=m+i;j++) add(x,2*y,j,z);
		}
	}
	printf("%d\n",(int)ans.size());
	for(auto [a,b,c,d]:ans) printf("%d %d %d %d\n",a,b,c,d);
}
int main(){
	int t=1;
	// scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}