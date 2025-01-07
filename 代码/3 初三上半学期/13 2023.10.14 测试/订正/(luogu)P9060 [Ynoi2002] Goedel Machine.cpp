#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353;
int n,m;
int a[N],ans[N];
int inv[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return ans;
}
int block;
struct node{int l,r,id;}q[N];
bool cmp(const node &a,const node &b){
	if(a.l/block!=b.l/block) return a.l<b.l;
	else return a.l/block&1?a.r<b.r:a.r>b.r;
}
int prime[N],cnt;
bool vis[N];
void get_prime(int x){
	for(int i=2;i<=x;i++){
		if(!vis[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt&&prime[j]*i<=x;j++){
			vis[prime[j]*i]=1;
			if(i%prime[j]==0) break;
		}
	}
}
int tmp[N];
int sum[N];
int first[N],pw[N];
int ans1=1,ans2=1;
void add(int x) {if(x!=1)ans1=ans1*pw[first[x]+sum[x]]%mod,sum[x]++;}
void del(int x) {if(x!=1)sum[x]--,ans2=ans2*pw[first[x]+sum[x]]%mod;}
signed main(){
	cin>>n>>m;
	int MAX=-1;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		MAX=max(MAX,a[i]);
	}
	get_prime(sqrt(MAX));
	block=n/sqrt(m);
	if(block==0) block=1;
	for(int i=1;i<=m;i++) {
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
		ans[i]=1;
	}
	inv[1]=1;
	for(int i=2;i<=MAX;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=cnt;i++) {
		int x=prime[i];
		tmp[0]=x;
		for(int j=1;j<=n;j++) tmp[j]=tmp[j-1]*tmp[j-1]%mod;
		for(int j=x;j<=MAX;j*=x) {
			for(int k=1;k<=n;k++)sum[k]=sum[k-1]+(a[k]%j==0);
			for(int k=1;k<=m;k++)ans[k]=ans[k]*tmp[sum[q[k].r]-sum[q[k].l-1]]%mod*inv[x]%mod;
		}
		for(int j=1;j<=n;j++) while(a[j]%x==0) a[j]/=x; 
	}
	for(int i=1;i<=MAX;i++) sum[i]=0;
	for(int i=1;i<=n;i++) sum[a[i]]++;
	int tot=0;
	for(int i=2;i<=MAX;i++) {
		if(sum[i]){
			first[i]=++tot;
			pw[first[i]]=i;
			while(--sum[i]) pw[tot+1]=pw[tot]*pw[tot]%mod,tot++;
		}
	}
	for(int i=1;i<=MAX;i++ )sum[i]=0;
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++) {
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		ans[q[i].id]=ans[q[i].id]*ans1%mod*qpow(ans2,mod-2)%mod;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}