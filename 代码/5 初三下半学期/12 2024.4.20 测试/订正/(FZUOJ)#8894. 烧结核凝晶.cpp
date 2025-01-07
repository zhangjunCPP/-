#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const double eps=1e-7;
int n,k;
struct node{
	int x,y;
	double val;
}a[N];
double tmp;
bool cmp(const node&x,const node&y){return x.x-tmp*x.y>y.x-tmp*y.y;}
bool check(double mid){
	sort(a+1,a+n+1,cmp);
	int ans1=0,ans2=0;
	for(int i=1;i<=k;i++)ans1+=a[i].x,ans2+=a[i].y;
	return (1.0*ans1/ans2)>mid;
}
signed main(){
	freopen("salt.in","r",stdin);
	freopen("salt.out","w",stdout);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
		a[i].val=a[i].x*1.0/a[i].y;
	}
	double l=0,r=1;
	while(r-l>eps){
		double mid=(l+r)/2;
		tmp=mid;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.6lf",l);
}