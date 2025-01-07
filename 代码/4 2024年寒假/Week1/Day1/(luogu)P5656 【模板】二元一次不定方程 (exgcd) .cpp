#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int gcd=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return gcd;
}
void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	int x,y;
	int gcd=exgcd(a,b,x,y);
	if(c%gcd){puts("-1");return;}
	x*=c/gcd,y*=c/gcd;
	int Min=floor(-1.0*x*gcd/b)+1;
	int Max=ceil(1.0*y*gcd/a)-1;
	if(Min<=Max){
		cout<<Max-Min+1<<" ";
		cout<<min(x+b/gcd*Min,x+b/gcd*Max)<<" "<<min(y-a/gcd*Max,y-a/gcd*Min)<<" ";
		cout<<max(x+b/gcd*Min,x+b/gcd*Max)<<" "<<max(y-a/gcd*Max,y-a/gcd*Min)<<"\n";
	}
	else{
		cout<<x+b/gcd*Min<<" "<<y-a/gcd*Max<<"\n";
	}
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}