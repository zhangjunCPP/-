#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+5,mod=998244353;

int read(){
	int s=0,w=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int T,n,maxd,fac[N],ifac[N],res[100];
int quick_power(int x,int y){
	int res=1;
	for (;y;y>>=1,(x*=x)%=mod) {if(y&1)(res*=x)%=mod;}
	return res;
}
void dfs(int l,int r,int d){
	maxd=max(maxd,d),(res[d]*=ifac[r-l+1])%=mod;
	if (l==r)  return;

	int mid=(l+r)>>1;
	dfs(l,mid,d+1),dfs(mid+1,r,d+1);
}
void solve(int k){
	if (k<=maxd)  printf("%lld\n",(fac[n]*res[k])%mod);
	else printf("%lld\n",fac[n]);
}
signed main(){
	T=read(),n=read(),fac[0]=1;
	for (int i=1;i<=n;i++)  fac[i]=(fac[i-1]*i)%mod;
	ifac[n]=quick_power(fac[n],mod-2);
	for (int i=n-1;~i;i--)  ifac[i]=(ifac[i+1]*(i+1))%mod;
	fill(res,res+100,1),dfs(1,n,0);

	while (T--)  solve(read());
	return 0;
}