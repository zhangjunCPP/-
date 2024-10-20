#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int INF=1e9;
int n,q;
int exgcd(int a,int b,int &x,int &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int g=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
int gcd(int x,int y){
	while(y^=x^=y^=x%=y);
	return x;
}
int inv(int a,int mod){
	int x,y;
	exgcd(a,mod,x,y);
	return (x%mod+mod)%mod;
}
int ans[N];
int pos[N];
int tmp[N],Min[N];
int dis(int x,int y){
	if(x<=y)return y-x;
	else return n-x+y;
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<n;i++)pos[i]=i;
	pos[0]=n;
	int delta1=0,delta2=1,m=n,t=1;
	while(q--){
		int opt,x;
		cin>>opt>>x;
		if(opt==1){
			int tmp=(x-delta1+n)%n;
			if(tmp%t==0)ans[pos[tmp*inv(delta2,m)%n]]++;
		}
		else if(opt==2)delta1=(delta1+x)%n;
		else{
			if(gcd(x,m)==1)delta1=delta1*x%n,delta2=delta2*x%n;
			else{
				for(int i=0;i<n;i+=t)tmp[i]=0,Min[i]=INF;
				for(int i=0;i<n;i+=t){
					int a=(i*delta2+delta1)%n;
					int b=a*x%n;
					int c=(b-x*delta1%n+n)%n;
					if(dis(a,b)<Min[c])Min[c]=dis(a,b),tmp[c]=pos[i];
				}
				int GCD=gcd(x,m);
				t*=GCD,m/=GCD;
				delta1=delta1*x%n,delta2=1;
				for(int i=0;i<n;i+=t)pos[i]=tmp[i];
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}