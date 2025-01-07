#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int prime[N],cnt;
bool vis[N];
int sum[N];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
	for(int i=2;i<N;i++)sum[i]=sum[i-1]+(!vis[i]);
}
void solve(){
	int n;
	cin>>n;
	cout<<sum[n]-sum[(int)sqrt(n)]+1<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	int T;
	cin>>T;
	while(T--)solve();
}//