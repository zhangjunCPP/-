
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
using namespace std;
const int N=2e6+5;

void file(){
	freopen("botbox.in","r",stdin);
	freopen("botbox.out","w",stdout);
}

char s[N];
int a[N],sum[N],b[N];
vector<pii>vec;
int n,k;

int trs(char c) {
	if(c=='A')return 2;
	if(c=='B')return 1;
	return 0;
}
char entrs(int x) {
	if(x==2)return 'A';
	if(x==1)return 'B';
	return 'C';
}

void solve(int l,int r) {
	int tim=k/n,pos=r+1,cnta=0,cntb=0;
	for(int i=l;i<=r;++i) {
		sum[i]=sum[i-1]*(i!=l)+(a[i]==a[l]);
		if(sum[i]>tim){
			pos=i;
			break;
		}
		if(a[i]==a[l])++cnta;
		else ++cntb;
	}
	
	for(int i=1;i<=cntb;++i)
		b[l+i-1]=(a[l]-1+3)%3;
	for(int i=pos;i<=r;++i)
		b[l+cntb+(i-pos)]=a[i];
	for(int i=1;i<=cnta;++i)
		b[l+cntb+r-pos+i]=a[l];
	
}

int q[N],hd,tl;

bool cmp(int u,int v){
	if(u==2&&v!=0)return true;
	if(u==1&&v!=2)return true;
	if(u==0&&v!=1)return true;
	return false;
}

void prepare(int rst) {
	k-=rst;
	for(int i=1;i<=n;++i) q[i]=a[i];
	hd=1,tl=n;
	while(rst--) {
		int u=q[hd],v=q[hd+1];
		++hd;
		if(cmp(u,v)) q[hd]=u,q[++tl]=v;
		else q[hd]=v,q[++tl]=u;
	}
	for(int i=hd;i<=tl;++i)
		a[i-hd+1]=q[i];
}
void advance() {
	int len=0;
	int u=a[vec.front().fi];
	int v=a[vec.back().fi];
	if(u==v)
		len=vec.front().se;
	else if((u-1+3)%3!=v)
		len=vec[1].se;
	prepare(min(len,k));
}
void work() {
	for(int l=1;l<=n;) {
		int ned=(a[l]+1)%3,r=l;
		while(r<=n&&a[r]!=ned)++r;
		solve(l,r-1);
		l=r;
	}
	
	int rst=k%n;
	for(int i=1;i<=n;++i) q[i]=b[i];
	hd=1,tl=n;
	while(rst--) {
		int u=q[hd],v=q[hd+1];
		++hd;
		if(cmp(u,v)) q[hd]=u,q[++tl]=v;
		else q[hd]=v,q[++tl]=u;
		
	}
	for(int i=hd;i<=tl;++i)
		putchar(entrs(q[i]));
}
void work2() {
	prepare(min(n, k));
	k %= (n - 1);
	prepare(k);
	for(int i = 1; i <= n; ++ i)
		putchar(entrs(a[i]));
}

void safe() {
	advance();
	work();
}

signed main(){
	 file();
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n>>k>>(s+1);
	
	int color=0;
	for(int i=1;i<=n;++i)a[i]=trs(s[i]),color|=(1<<a[i]);
	
	for(int l=1;l<=n;) {
		int ned=(a[l]+1)%3,r=l;
		while(r<=n&&a[r]!=ned)++r;
		vec.push_back(pii(l,r-1));
		l=r;
	}
	
	if(vec.size() >= 3) return safe(),0;
	if(vec.size()==1) return work2(),0;
	if(vec.size()==2) {
		prepare(min(vec[0].se,k));
		if(color==7) work();
		else work2();
		return 0;
	}
	puts("QWQ");
	return 0;
}
// 9:00idea
//9:40 test4/yiw
//10:00 test4/fn
//10:40 finally.
