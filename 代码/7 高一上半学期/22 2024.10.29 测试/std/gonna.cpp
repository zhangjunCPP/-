#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=5e5+5;
int n,m,a[N],le[N],q[N],h,t;
ll dp[N];
signed main(){
	n=read();
	repn(i)a[i]=read();a[n+1]=0;
	rep(i,1,n+1)le[i]=0;
	m=read();
	while(m--){
		int l=read(),r=read();
		le[r+1]=max(le[r+1],l);
	}
	int lim=0;
	q[h=t=1]=0;
	rep(i,1,n+1){
		lim=max(lim,le[i]);
		while(h<=t&&q[h]<lim)h++;
		dp[i]=dp[q[h]]+a[i];
		while(h<=t&&dp[i]<=dp[q[t]])t--;
		q[++t]=i;
	}
	cout <<dp[n+1]<<'\n';
	return 0;
}