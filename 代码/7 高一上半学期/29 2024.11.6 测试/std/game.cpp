#include<bits/stdc++.h>
using namespace std;
using i64=long long;
constexpr i64 mod=1000000007;
inline i64 qpow(i64 p,i64 t){
	i64 r=1;for(;t;t>>=1,p=p*p%mod)if(t&1)(r*=p)%=mod;
	return r;
}
int n,A,B,C,X;
i64 fac[1010],ifac[1010],inv[1010],cat[1010],f[510][510],g[510][510],ans[510];
inline i64 binom(int n,int m){
	return m<0||m>n?0:fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
namespace lag{
	i64 val[1010],f[1010];
	void calc(){
		f[1]=1;for(int i=1;i<=n/2;i++){
			for(int j=n/2+1;j;j--){
				f[j]=(f[j-1]+(mod-i)*f[j])%mod;
			}
		}
		copy_n(ans,n/2+1,val),fill_n(ans,n/2+1,0);
		for(int i=0;i<=n/2;i++){
			i64 w=val[i]*ifac[i]%mod*ifac[n/2-i]%mod*(n/2-i&1?mod-1:1)%mod,v=0;
			for(int k=n/2+1;k;k--){
				v=(v*i+f[k])%mod,(ans[k-1]+=v*w)%=mod;
			}
		}
	}
}
void init(int n){
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[1]=1;for(int i=2;i<=n;i++)inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	ifac[0]=1;for(int i=1;i<=n;i++)ifac[i]=ifac[i-1]*inv[i]%mod;
	for(int i=1;i<=n/2;i++)cat[i]=binom(i*2,i)*inv[i+1]%mod;
}
void init2(){
	f[0][0]=1;
	for(int i=1;i<=n/2;i++){
		f[i][1]=cat[i];
		for(int j=1;j<i;j++)(f[i][1]+=(mod-cat[j])*f[i-j][1])%=mod;
	}
	for(int i=1;i<=n/2;i++)for(int j=2;j<=i;j++)for(int k=0;k<i;k++)
		(f[i][j]+=f[k][j-1]*f[i-k][1])%=mod;
	for(int i=0;i<=n/2;i++){
		for(int k=0;k<=n/2;k++){
			for(int j=i;j>=0;j--){
				g[i][k]=(g[i][k]*k+f[i][j]*ifac[j])%mod;
			}
		}
	}
}
int main(){
	scanf("%d%d%d%d",&A,&B,&C,&X),n=A+B+C;
	assert(1<=A&&A<=1000);
	assert(1<=B&&B<=1000);
	assert(1<=C&&C<=1000);
	assert(A+B+C<=1000);
	assert(1<=X&&X<=1000000000);
	if(n&1||max({A,B,C})>n/2)return puts("0"),0;
	init(n+2),init2();
	for(int a=0;a<=A;a++)for(int b=0;b<=B&&a+b<=n/2;b++){
		int c=n/2-a-b;
		i64 coef=0;
		for(int ab=0;ab<=A-a;ab++){
			int ac=A-a-ab,bc=c-ac,cb=b-ab,ba=B-b-bc,ca=c-cb;

			(coef+=binom(a,ba)*binom(b,ab)%mod*binom(c,ac))%=mod;
		}
		for(int k=0;k<=n/2;k++)(ans[k]+=g[a][k]*g[b][k]%mod*g[c][k]%mod*coef)%=mod;
	}
	lag::calc();
	i64 x=0;
	for(int k=0;k<=n/2;k++)(x+=qpow(k,X)*ans[k]%mod*fac[k])%=mod;
	printf("%lld",x);
	return 0;
}