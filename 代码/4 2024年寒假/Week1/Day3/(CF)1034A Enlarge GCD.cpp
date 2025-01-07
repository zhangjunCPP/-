#include<bits/stdc++.h>
using namespace std;
const int N=2e7+10;
int prime[N],cnt;
bool vis[N];
void init(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int gcd(int x,int y){
	while(y^=x^=y^=x%=y);
	return x;
}
int a[N];
int tot[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int Gcd=a[1];
	for(int i=2;i<=n;i++)Gcd=gcd(Gcd,a[i]);
	int Max=-1;
	for(int i=1;i<=n;i++)a[i]/=Gcd,Max=max(Max,a[i]),tot[a[i]]++;
	init(Max);
	int ans=n;
	for(int i=1;i<=cnt;i++){
		int tmp=prime[i];
		int sum=0;
		for(int j=tmp;j<=Max;j+=tmp)sum+=tot[j];
		ans=min(ans,n-sum);
	}
	if(ans==n)ans=-1;
	cout<<ans;
}