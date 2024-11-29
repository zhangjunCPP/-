#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
int prime[N],cnt;
bool vis[N];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
void calc(int x,vector<int> &pri){
	for(int i=1;i<=cnt&&prime[i]*prime[i]<=x;i++){
		while(x%prime[i]==0){
			x/=prime[i];
			pri.push_back(prime[i]);
		}
	}
	if(x!=1)pri.push_back(x);
}
vector<int> pri_x,pri_y;
void solve(){
	pri_x.clear(),pri_y.clear();
	int x,y;
	cin>>x>>y;
	if(x==1||y==1){cout<<"1\n";return;}
	calc(x,pri_x);calc(y,pri_y);
	int gcd=__gcd(pri_x.back(),pri_y.back());
	if(gcd==1||pri_x.back()>(long long)gcd*gcd||pri_y.back()>(long long)gcd*gcd){cout<<"1\n";return;}
	if(pri_x.back()!=gcd)pri_x.back()/=gcd,pri_x.push_back(gcd);
	if(pri_y.back()!=gcd)pri_y.back()/=gcd,pri_y.push_back(gcd);
	int ans=1;
	while(true){
		if(pri_x.empty()||pri_y.empty())break;
		if(pri_x.back()!=pri_y.back())break;
		ans*=pri_x.back();
		pri_x.pop_back(),pri_y.pop_back();
	}
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}