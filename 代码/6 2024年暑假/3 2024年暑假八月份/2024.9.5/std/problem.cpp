#include<bits/stdc++.h>
#define int long long
#define N ((int)2e5+2)	
#define pq priority_queue<int>
#define mod ((int)1e9)			
using namespace std;
namespace STD{
	inline int read(){
		int s=0,t=1;
		char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') t=-1;ch=getchar();}
		while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
		return s*t;
	}
	inline void write(int x){
		if(x<0) x=~(x-1),putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void io(){cin.tie(nullptr),cout.tie(nullptr);}
	inline void swap(int &a,int &b){a^=b^=a^=b;}
	inline int min(int a,int b){return ((a<b)?a:b);}
	inline int max(int a,int b){return ((a>b)?a:b);}
	struct Pair{int fir,sec;};
	inline bool Pair_cmp(Pair x,Pair y){
		if(x.fir==y.fir) return x.sec<y.sec;
		return x.fir<y.fir;
	}
	#define INF ((int)2e9+2)
	inline void pre_max_0(int *a,int len){for(int i=0;i<len;++i) a[i]=INF;}
	inline void pre_min_0(int *a,int len){for(int i=0;i<len;++i) a[i]=-INF;}
	inline void pre_max(int *a,int len){for(int i=1;i<=len;++i) a[i]=INF;}
	inline void pre_min(int *a,int len){for(int i=1;i<=len;++i) a[i]=-INF;}
}
using namespace STD;
int a[N],b[N];
char opt[N];
priority_queue<int> q[N];
int L[N],R[N],cnt;
int n,m,T;
inline void merge(pq &u,pq &v){
while(!v.empty()) u.push(v.top()),v.pop();}
inline void del(int x){
	merge(q[x],q[R[R[x]]]),merge(q[R[x]],q[R[R[R[x]]]]);
	R[R[x]]=R[R[R[R[x]]]],L[R[R[x]]]=R[x];
}
inline void solve(int x){
	for(int i=4,y=x;i;--i,y=R[y]) if(y==R[y]) return;
	if(q[x].empty() || q[R[x]].empty()) return;
	if(q[R[x]].top()+q[R[R[x]]].top()<=0) del(x);
}
signed main(){
	n=read(),m=read(),T=read();
	scanf("%s",opt+1);
	for(int i=1;i<=m;++i)
		b[i]=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1,j=1;i<=m;i=j){
		for(;j<=m&&opt[i]==opt[j];++j);
		if(opt[i]=='0'){
			++cnt;
			for(int k=i;k<j;++k)
				q[cnt].push(b[k]);
		}
		else{
			++cnt;
			for(int k=i;k<j;++k)
				q[cnt].push(-b[k]);
		}
	}
	for(int i=1;i<=cnt;++i) R[i]=i+1,L[i]=i-1;
	R[cnt]=cnt;
	for(int j=1;j!=R[j];j=R[j])
		solve(j);
	int last=0;
	for(int i=1;i<=n;++i){
		int w=(a[i]+T*last)%mod;
		for(int j=1;;j=R[j]){
			if(q[j].top()<0&&-q[j].top()<w){
				int v=-q[j].top();
				q[j].pop();q[j].push(-w);
				w=v;
			}
			else if(q[j].top()>0&&q[j].top()>w){
				int v=q[j].top();
				q[j].pop();q[j].push(w);
				w=v;
			}
			if(j==R[j])
				break;
		}
		printf("%lld ",last+=w);
		for(int j=1;j!=R[j];j=R[j])
			solve(j);
	}
return 0;
}