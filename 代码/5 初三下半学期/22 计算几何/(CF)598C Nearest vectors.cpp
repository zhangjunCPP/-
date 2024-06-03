#include <bits/stdc++.h>
#define double long double
using namespace std;
const int N=1e5+10;
const double pi= acos(-1);
struct point{
	int id;
	double x,y,phi;
	double calc_phi()const{return atan2(y,x);}
}a[N];
bool cmp(const point&x,const point&y){return x.phi<y.phi;}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		a[i].phi=a[i].calc_phi();
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	double Min=a[1].phi-a[n].phi+2*pi;
	int ans1=a[1].id,ans2=a[n].id;
	for(int i=2;i<=n;i++){
		double tmp=a[i].phi-a[i-1].phi;
		if(tmp<Min){
			Min=tmp;
			ans1=a[i].id,ans2=a[i-1].id;
		}
	}
	cout<<ans1<<" "<<ans2;
}