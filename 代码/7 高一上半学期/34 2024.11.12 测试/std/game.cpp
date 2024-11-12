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
const int N=1000+5,M=1e6+5,K=1e7+5,mod=998244353,Mod=mod-1;const db eps=1e-9;const ll INF=5e18+7;mt19937 rnd(time(0));
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
int n,A[N],B[N],id[N];
void Solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&A[i]);
	for(int i=1;i<=n;i++) B[A[i]]=i;
	int cnt=0;
	for(int i=1;i<=n;i++){
		int r=i;while(r<=n&&B[r+1]>B[r]) r++;
		cnt++;for(int j=i;j<=r;j++) id[j]=cnt;
		i=r;
	}
	int k=__lg(cnt*2-1);
	vector<string> ans(k);
	for(int i=0;i<k;i++){
		queue<int> q1,q2;
		for(int j=1;j<=n;j++){
			if(id[A[j]]-1>>i&1) q2.push(A[j]),ans[i]+='B';
			else q1.push(A[j]),ans[i]+='A';
		}
		for(int j=1;j<=n;j++){
			if(q1.empty()) A[j]=q2.front(),q2.pop();
			else A[j]=q1.front(),q1.pop();
		}
	}
	reverse(all(ans));
	printf("%d\n",int(ans.size()));
	for(auto i:ans){
		for(char j:i) putchar(j);
		putchar('\n');
	}
}
int main(){
	int t=1;
	scanf("%d",&t);
	while(t--) Solve();
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<'\n';
}