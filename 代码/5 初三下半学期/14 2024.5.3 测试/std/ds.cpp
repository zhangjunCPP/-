#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 
int read() {
	int x=0; char ch=getchar();  
	while (!isdigit(ch)) ch=getchar();  
	while (isdigit(ch)) x=x*10+ch-48, ch=getchar();  
	return x;  
}

const int mod=998244353;
void inc(int &x, int y) {
	x+=y;
	if (x>=mod) x-=mod;
}
int fpow(ll a, int b=mod-2) {
	int res=1;
	while (b) {
		if (b&1) res=res*a%mod;
		a=a*a%mod, b>>=1;
	}
	return res;
}

const int N=5e5+3;
int n, m, a[N];

int fac[N<<1], ifa[N<<1];
void init(const int n) {
	fac[0]=1;
	for (int i=1; i<=n; i++) fac[i]=1ll*fac[i-1]*i%mod;
	ifa[n]=fpow(fac[n]);
	for (int i=n-1; ~i; i--) ifa[i]=ifa[i+1]*(i+1ll)%mod;
}
inline ll C(int x, int y) {
	if (x<y||y<0) return 0;
	return 1ll*fac[x]*ifa[y]%mod*ifa[x-y]%mod;
}

int T;
struct node {
	int pos, w, tim;

	ll ask(int x) {
		if (pos>x) return 0ll;
		const int t=T-tim;
		return w*C(t+x-pos, t)%mod;
	}
};
vector<node> b;

int main() {
    freopen("ds.in","r",stdin);
    freopen("ds.out","w",stdout);
	n=read(), m=read();
	init(m+n);
	T=1, b.push_back({1, 1, 0});
	while (m--) {
		int opt=read();
		if (opt==1) T++;
		else if (opt==2) {
			int p=read();
			b.push_back({p, read(), T});
		} else {
			int l=read(), r=read(), ans=0;
			for (auto &it:b) {
				ans=(ans+it.ask(r)-it.ask(l-1)+mod)%mod;
			}
			printf("%d\n", ans);
		}
	}
    return 0;
}