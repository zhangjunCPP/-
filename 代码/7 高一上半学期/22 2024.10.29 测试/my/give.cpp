#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10,mod=1e9+7;
int tot[10];
inline int f(int x){
	for(int i=0;i<10;i++)tot[i]=0;
	while(x)tot[x%10]++,x/=10;
	int Max=0;
	for(int i=0;i<10;i++)Max=max(Max,tot[i]);
	for(int i=9;i>=0;i--)if(tot[i]==Max)return i;
}
int sum[N];
void init(){
	for(int i=1;i<N;i++)sum[i]=(sum[i-1]+f(i))%mod;
}
void solve(){
	int n;
	cin>>n;
	cout<<sum[n]<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}