#include <algorithm>
#include <iostream>
#include <math.h> 
using namespace std;

typedef long long ll;
ll read() {
	ll x=0; char ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=x*10+ch-48, ch=getchar();
	return x;
}

int n;
ll C;

void print(int a, int b, int c, int d, int k) {
	int cnt=4-(!a)-(!b)-(!c)-(!d);
	if (k<cnt) return puts("-1"), void();
	ll res=0;
	k-=4;
	k++; if (k>=1) res+=1ll*k*k*a;
	k++; if (k>=1) res+=1ll*k*k*b;
	k++; if (k>=1) res+=1ll*k*k*c;
	k++; if (k>=1) res+=1ll*k*k*d;
	printf("%lld\n%d\n", res, k);
	k-=4;
	for (int i=1; i<=k; i++) printf("0 ");
	k++; if (k>=1) printf("%d ", a);
	k++; if (k>=1) printf("%d ", b);
	k++; if (k>=1) printf("%d ", c);
	k++; if (k>=1) printf("%d ", d);
	return puts(""), void();
}
void solve() {
	n=read(), C=read();
	ll p=ceil(1.0*C/n);
	int x=n*p-C, y=n-x;
	if (p>n||p==0) return puts("-1"), void();
	if (x<=y) return print(0, 0, x, y, p);
	int t=ceil((x-y)/3.0);
	x-=t*2, y+=t;
	if (t<=x) return print(0, t, x, y, p);
	if (t<=2) return puts("-1"), void();
	return print(1, t-2, x+1, y, p);
}

int T;

int main() {
    freopen("gz.in","r",stdin);
    freopen("gz.out","w",stdout);
	T=read();
	while (T--) solve();
	return 0;
}