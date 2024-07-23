#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=998244353;
int n,m;
int a[N];
int block;
struct node{
	int l,r;
	int id;
}q[N];
bool cmp(const node&x,const node&y){
	if(x.l/block==y.l/block)return (x.l/block)&1?x.r<y.r:x.r>y.r;
	return x.l<y.l;
}
int cnt[N];
int dp[N];
void update(int opt,int x){
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
int fac[N];
int ans[N];
signed main(){
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	cin>>n>>m;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	dp[0]=1;
	block=sqrt(n*n/m);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].l++;
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
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

/*
这是谁出的题，每次比赛都有原题。（好像第二次考试没有？）
之前的原题都没写出来，今天终于让我碰上了。
--------
考虑容斥。
钦定有i种数重复，且每种数只重复1次，其余的数不管。
记每种数x的数量为cnt_x，区间长度为n
比如说：钦定有2种数重复，而且每个数只重复1次，也就是说，有n-2个位置任意放
设区间内有四种数，数量为cnt1~4。
那么贡献为：
(cnt1cnt2+cnt1cnt3+cnt1cnt4+cnt2cnt3+cnt2cnt4+cnt3cnt4)*fac[n-2]
其实想一想挺显然的
莫队维护cnt，动态添加即可
也可以使用多项式：对于每种数x，构造多项式为：\sum_i cnt_xx^i
相乘即可。
复杂度更优，但没必要
而且当时做这道题是还没学多项式
--------
wc，刚刚看div3的T1也是之前我们考过的原题！比较简单
 */