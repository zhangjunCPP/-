#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
const int N=1e6+10;
int n,k;
struct node{
	double x,y;
	double val;
}a[N];
bool cmp(const node&x,const node&y){return x.val>y.val;}
bool check(double mid){
	for(int i=1;i<=n;i++)a[i].val=a[i].x-a[i].y*mid;
	sort(a+1,a+n+1,cmp);
	double ans=0;
	for(int i=1;i<=n-k;i++)ans+=a[i].val;
	return (ans>0);
}
int main(){
	cin>>n>>k;
	while(n!=0||k!=0){
		for(int i=1;i<=n;i++)cin>>a[i].x;
		for(int i=1;i<=n;i++)cin>>a[i].y;
		double l=0,r=1;
		while(r-l>eps){
			double mid=(l+r)/2;
			if(check(mid))l=mid;
			else r=mid;
		}
		printf("%.0lf\n",100*l);
		cin>>n>>k;
	}
}