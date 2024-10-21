#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
int mx[19][maxn];
bool cmp(int u,int v){return a[u]<a[v];}
int que(int l,int r){
	int k=log2(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1],cmp);
}
int pl[maxn],pr[maxn],pos[maxn];
void build(int l,int r){
	if(l>r)return ;
	int mid=que(l,r);
	build(l,mid-1),build(mid+1,r);
	pl[mid]=l,pr[mid]=r,pos[a[mid]]=mid;
}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int pw1[maxn],pw2[maxn];
inline int pw(int x){return pw2[x/maxn]*pw1[x%maxn]%mod;}
int f[maxn],dp[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)mx[0][i]=i;
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)],cmp);
	}
	build(1,n);
	for(int i=0;i<=n;i++)dp[i]=f[i]=0;
	dp[0]=dp[pos[1]]=1;
	int mul=1,inv=1;
	for(int i=2;i<=n;i++){
		int u=pos[i],l=pl[u],r=pr[u];
		f[0]=dp[0]*mul%mod;for(int j=l;j<=r;j++)f[j]=dp[j]*mul%mod;
		dp[0]=0;for(int j=l;j<=r;j++)dp[j]=0;
		mul=mul*(pw((u-l+1)*(r-u+1))-1)%mod,inv=inv*ksm(pw((u-l+1)*(r-u+1))-1)%mod;
		(dp[0]+=f[0]*(pw((u-l+1)*(r-u+1))-1)%mod*inv)%=mod;
		(dp[u]+=f[0]*inv)%=mod;
		for(int j=l;j<u;j++){
			(dp[j]+=f[j]*(pw((u-j)*(r-u+1))-1)%mod*inv)%=mod;
			(dp[0]+=f[j]*(pw((u-j)*(r-u+1))-1)%mod*(pw((j-l+1)*(r-u+1))-1)%mod*inv)%=mod;
		}
		for(int j=u+1;j<=r;j++){
			(dp[j]+=f[j]*(pw((u-l+1)*(j-u))-1)%mod*inv)%=mod;
			(dp[0]+=f[j]*(pw((u-l+1)*(j-u))-1)%mod*(pw((u-l+1)*(r-j+1))-1)%mod*inv)%=mod;
		}
		// cout<<i<<"\n";
		// for(int j=0;j<=n;j++)cout<<dp[j]*mul%mod<<" ";cout<<"\n";
	}
	ans=0;for(int i=0;i<=n;i++)ans+=dp[i];ans%=mod;ans=ans*mul%mod;
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){


	T=read();
	pw1[0]=1;for(int i=1;i<maxn;i++)pw1[i]=pw1[i-1]*2%mod;
	pw2[0]=1;for(int i=1;i<maxn;i++)pw2[i]=pw2[i-1]*2*pw1[maxn-1]%mod;
	while(T--)work();
}