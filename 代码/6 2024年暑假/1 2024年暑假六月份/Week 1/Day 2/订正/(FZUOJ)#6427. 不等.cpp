#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int n,m;
int a[N];
int block;
struct node{
	int l,r;
	int id;
}q[N];
bool cmp(const node&x,const node&y){
	if(x.l/block==y.l/block)return (x.l/block)&1?x.r<y.r:x.r>y.r;
	else return x.l<y.l;
}
int dp[N];
int cnt[N];
void update(bool opt,int x){
	if(opt)for(int i=n;i;i--)dp[i]=(dp[i]+dp[i-1]*x%mod)%mod;
	else for(int i=1;i<=n;i++)dp[i]=(dp[i]-dp[i-1]*x%mod+mod)%mod;
}
void add(int x){
	update(0,cnt[x]);
	update(1,++cnt[x]);
}
void del(int x){
	update(0,cnt[x]);
	update(1,--cnt[x]);
}
int ans[N];
int fac[N];
signed main(){
	cin>>n>>m;
	block=sqrt(n*n/m);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].l++;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	dp[0]=1;
	int L=1,R=0;
	for(int i=1;i<=m;i++){
		while(L>q[i].l)add(a[--L]);
		while(R<q[i].r)add(a[++R]);
		while(L<q[i].l)del(a[L++]);
		while(R>q[i].r)del(a[R--]);
		int len=q[i].r-q[i].l+1;
		for(int j=0;j<=len;j++)ans[q[i].id]=(ans[q[i].id]+((j&1)?-1:1)*dp[j]*fac[n-j]+mod)%mod;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}