#include <bits/stdc++.h>
#define ll __int128
using namespace std;
const int N=1000+10;
ll read() {
	ll x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(ll x) {
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int ls(const int x){return x<<1;}
int rs(const int x){return x<<1|1;}
ll gcd(ll x,ll y) {
	if(!x||!y)return x+y;
	while(x^=y^=x^=y%=x);
	return y;
}
struct node {
	ll tree[4*N];
	void update(int k,int l,int r,int x,ll y) {
		if(l==r) {
			tree[k]=y;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid)update(ls(k),l,mid,x,y);
		else update(rs(k),mid+1,r,x,y);
		tree[k]=gcd(tree[ls(k)],tree[rs(k)]);
	}
}Tree1[N],Tree2[N];
ll a[N],b[N];
bool vis1[N],vis2[N];
void solve() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)Tree1[i].update(1,1,m,j,a[i]/gcd(a[i],b[j]));
	for(int i=1;i<=m;i++)for(int j=1;j<=n;j++)Tree2[i].update(1,1,n,j,b[i]/gcd(b[i],a[j]));
	memset(vis1,false,sizeof vis1);
	memset(vis2,false,sizeof vis2);
	int sum1=n,sum2=m;
	while(sum1||sum2) {
		bool flag=false;
		for(int i=1;i<=n;i++) {
			if(!vis1[i]&&Tree1[i].tree[1]!=1) {
				flag=true;
				vis1[i]=true;
				sum1--;
				for(int j=1;j<=m;j++)Tree2[j].update(1,1,n,i,0);
			}
		}
		for(int i=1;i<=m;i++) {
			if(!vis2[i]&&Tree2[i].tree[1]!=1) {
				flag=true;
				vis2[i]=true;
				sum2--;
				for(int j=1;j<=n;j++)Tree1[j].update(1,1,m,i,0);
			}
		}

		if(!flag)break;
	}
	if(sum1==0||sum2==0){cout<<"NO\n";return;}
	cout<<"YES\n"<<sum1<<" "<<sum2<<"\n";
	for(int i=1;i<=n;i++)if(!vis1[i]){write(a[i]);putchar(' ');}
	cout<<"\n";
	for(int i=1;i<=m;i++)if(!vis2[i]){write(b[i]);putchar(' ');}
	cout<<"\n";
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
}