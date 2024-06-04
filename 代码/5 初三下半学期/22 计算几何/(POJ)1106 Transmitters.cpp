#include <cmath>
#include <iostream>

using namespace std;
const int N=1e5+10;
const double eps=1e-6;
const double pi=acos(-1);

int sgn(double x){return x<-eps?-1:x>eps;}
struct point{
	int x,y;
	void init(){cin>>x>>y;}
	point operator+(const point&oth) const{return point{x+oth.x,y+oth.y};}
	point operator-(const point&oth) const{return point{x-oth.x,y-oth.y};}
	int operator*(const point&oth) const{return x*oth.x+y*oth.y;}//点乘
	int operator%(const point&oth) const{return x*oth.y-y*oth.x;}//叉乘
}a[N];
int main(){
	point o;
	double r;
	while(cin>>o.x>>o.y>>r){
		if(r<0)break;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)a[i].init();
		for(int i=1;i<=n;i++)a[i]=a[i]-o;
		int ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]*a[i]<=0)continue;
			if(a[i]*a[i]<=r*r){
				int sum=0;
				for(int j=1;j<=n;j++)if(a[j]*a[j]<=r*r&&a[j]%a[i]>=0)sum++;
				ans=max(ans,sum);
			}
		}
		cout<<ans<<"\n";
	}
}