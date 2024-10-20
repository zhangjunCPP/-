#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=998244353;
int n,m,c;
const int maxn=2e5+45;
vector<int> v[maxn];
int w[maxn],a[maxn];
int jc[maxn],inv[maxn];
inline int C(int x,int y){
	if(x<y || x<0 || y<0) return 0;
	return (ll)jc[x]*inv[y]%mod*inv[x-y]%mod;
}
int f[maxn][33][2],g[maxn][33][2];
inline int MOD(int x){
	return x>=mod?x-mod:x;
}
inline void ADD(int &x,int y){
	x=MOD(x+y);
}
int main(){
	scanf("%d%d%d",&n,&m,&c);
	jc[0]=1;
	for(int i=1;i<=n+m;i++) jc[i]=(ll)jc[i-1]*i%mod;
	inv[0]=inv[1]=1;
	for(int i=2;i<=n+m;i++) inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=n+m;i++) inv[i]=(ll)inv[i]*inv[i-1]%mod;
	for(int i=1;i<=n+1;i++) scanf("%d",&w[i]);
	for(int i=1;i<=c;i++) scanf("%d",&a[i]);
	f[0][0][0]=1;
	for(int i=1;i<=n+m;i++){
		for(int j=0;j<=min(i,m);j++){//当前填了 j 个特殊石子
			if(j){
				ADD(f[i][j][1],f[i-1][j-1][0]);
				ADD(f[i][j][1],f[i-1][j-1][1]);
				ADD(g[i][j][1],g[i-1][j-1][0]);
				ADD(g[i][j][1],g[i-1][j-1][1]);
				if(j==1){
					ADD(g[i][j][1],(ll)f[i-1][j-1][0]*w[i]%mod);
					ADD(g[i][j][1],(ll)f[i-1][j-1][1]*w[i]%mod);
				}
			}
			ADD(f[i][j][0],f[i-1][j][0]);
			ADD(f[i][j][0],f[i-1][j][1]);
			ADD(g[i][j][0],g[i-1][j][0]);
			ADD(g[i][j][0],g[i-1][j][1]);
		}
	}
	int ans=0;
	int s=1;
	for(int i=1;i<=c;i++) s=(ll)s*inv[a[i]]%mod;
	for(int i=1;i<=c;i++){
		v[i].resize(a[i]+1);
		for(int j=1;j<=a[i];j++){
			scanf("%d",&v[i][j]);
			int re=n+m-j;
			int s2=(ll)s*jc[a[i]]%mod*inv[a[i]-j]%mod;
			int ca1=MOD((ll)s2*jc[n-j]%mod-((j==a[i])?0ll:((ll)s2*jc[n-j-1]%mod*jc[a[i]-j]%mod*inv[a[i]-j-1]%mod))+mod);
			int ca2=(ll)s2*jc[n-j]%mod;
			// cout<<i<<" "<<j<<" "<<re<<" "<<g[re][m][0]<<" "<<ca1<<" "<<g[re][m][1]<<" "<<ca2<<endl;
			int sum=MOD((ll)g[re][m][0]*ca1%mod+(ll)g[re][m][1]*ca2%mod);
			ans=MOD(ans+(ll)sum*v[i][j]%mod);
		}
	}
	ans=MOD(ans+(ll)g[n+m][m][1]*jc[n]%mod*s%mod);
	printf("%d",ans);
	return 0;
}