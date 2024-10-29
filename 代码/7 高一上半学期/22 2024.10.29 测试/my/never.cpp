#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e7+10;
bool vis[N];
int prime[N],cnt;
int Min[N];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i]){Min[i]=i;prime[++cnt]=i;}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			Min[i*prime[j]]=prime[j];
			if(i%prime[j]==0)break;
		}
	}
}
ll lcm(int x,int y){
	int gcd=__gcd(x,y);
	return (ll)x/gcd*y;
}
void solve(){
	int a,b;
	cin>>a>>b;
	if(a%b==0||b%a==0){
		cout<<lcm(a,b)<<"\n";
		return;
	}
	if(__gcd(a,b)!=1){
		cout<<a+b<<"\n";
		return;
	}
	//一共就5个点:a,Min[a],2,Min[b],b,讨论完所有路径即可
	ll lcm1=lcm(a,2),lcm2=lcm(b,2),lcm3=lcm(Min[a],2),lcm4=lcm(Min[b],2);
	ll ans1=a+lcm3+lcm4+b;
	ll ans2=a+lcm3+lcm2;
	ll ans3=a*Min[b]+b;
	ll ans4=a+Min[a]*b;
	ll ans5=a+Min[a]*Min[b]+b;
	ll ans6=a*b;
	ll ans7=lcm1+lcm2;
	ll ans8=lcm1+lcm4+b;
	cout<<min({ans1,ans2,ans3,ans4,ans5,ans6,ans7,ans8})<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}