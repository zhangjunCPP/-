#include<bits/stdc++.h>
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;
inline int qr() {
	char c;bool f(1);
	while(!isdigit(c=getchar()))f=c!='-';
	int x(c^48);
	while(isdigit(c=getchar()))x=x*10+(c^48);
	return f?x:-x;
}
const int N(40);
const int M(1<<20|5);
const int P(2000019);
const int pw[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
int n,a[N+5],hn,ans;;
int b[15][M+5],totb,c[15][M+5],totc;

void dfs1(int x,int sum) {
	if(x>hn) return (void)(b[9][++totb]=sum);
	dfs1(x+1,sum),dfs1(x+1,sum+a[x]);
}
void dfs2(int x,int sum) {
	if(x>n) return (void)(c[9][++totc]=sum);
	dfs2(x+1,sum),dfs2(x+1,sum+a[x]);
}
void Sortb() {
	U(k,0,8) {
		basic_string<int>v[15];
		int cnt(0);
		if(k)U(i,1,totb) v[b[k-1][i]%pw[k+1]/pw[k]]+=b[k-1][i];
		else U(i,1,totb) v[b[9][i]%pw[1]]+=b[9][i];
		U(i,0,9) {
			for(auto j:v[i]) b[k][++cnt]=j;
			if(cnt==totb) break;
		}
	}
	U(i,0,8) U(j,1,totb) b[i][j]%=pw[i+1],assert(j==1||b[i][j]>=b[i][j-1]);
}
void Sortc() {
	U(k,0,8) {
		basic_string<int>v[15];
		int cnt(0);
		if(k)U(i,1,totc) v[c[k-1][i]%pw[k+1]/pw[k]]+=c[k-1][i];
		else U(i,1,totc) v[c[9][i]%pw[1]]+=c[9][i];
		U(i,0,9) {
			for(auto j:v[i]) c[k][++cnt]=j;
			if(cnt==totc) break;
		}
	}
	U(i,0,8) U(j,1,totc) c[i][j]%=pw[i+1],assert(j==1||c[i][j]>=c[i][j-1]);
}

inline void dec(int &a,int b) {
	if((a-=b)<0) {
		a+=P;
	}
}
inline void inc(int &a,int b) {
	if((a+=b)>=P) {
		a-=P;
	}
}

void Solve() {
	U(i,0,8) {
		int r(totb+1),tmp(4*pw[i]);
		U(l,1,totc) {
			while(r>1&&c[i][l]+b[i][r-1]>=tmp) --r;
			dec(ans,r);
		}
	}
	U(i,0,8) {
		int r(totb+1),tmp(5*pw[i]-1);
		U(l,1,totc) {
			while(r>1&&c[i][l]+b[i][r-1]>tmp) --r;
			inc(ans,r);
		}
	}
	U(i,0,8) {
		int r(totb+1),tmp(4*pw[i]+pw[i+1]);
		U(l,1,totc) {
			while(r>1&&c[i][l]+b[i][r-1]>=tmp) --r;
			dec(ans,r);
		}
	}
	U(i,0,8) {
		int r(totb+1),tmp(5*pw[i]-1+pw[i+1]);
		U(l,1,totc) {
			while(r>1&&c[i][l]+b[i][r-1]>tmp) --r;
			inc(ans,r);
		}
	}
}

signed main() {
	n=qr(),hn=n>>1;
	U(i,1,n) a[i]=qr();
	dfs1(1,0),dfs2(hn+1,0),Sortb(),Sortc();
	Solve();
	printf("%d",ans);
	assert(0<=ans&&ans<P);
}