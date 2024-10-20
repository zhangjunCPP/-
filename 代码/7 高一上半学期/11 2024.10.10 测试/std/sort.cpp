#include<bits/stdc++.h>
const int N(1e7+10),Mod(998244353);
int L,R,n,fac[N],inv[N],f[N],g[N],ans;
int main()
{
	std::scanf("%d%d", &L, &R),n=R,fac[0]=inv[1]=1;
	for(int i=1;i<=n+1;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<=n+1;i++)inv[i]=1ll*(Mod-Mod/i)*inv[Mod%i]%Mod;
	for(int i=1;i<=n;i++)
		f[i]=(f[i-1]+1ll*i*inv[i+1])%Mod,g[i]=(g[i-1]-1ll*(1ll*i*i-i+1)%Mod*inv[i])%Mod;
	for(int i=L,res;i<=R;i++)
		res=(1ll*f[i]*fac[i+1]+1ll*g[i]*fac[i])%Mod,ans^=(res+Mod)%Mod;
	printf("%d\n",ans);
	return 0;
}