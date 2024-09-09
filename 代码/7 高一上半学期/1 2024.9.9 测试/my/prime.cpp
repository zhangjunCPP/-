#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
bool vis[N];
int prime[N],cnt;
int sum[N];
void init(){
	vis[0]=true;
	vis[1]=true;
	sum[1]=0;
	for(int i=2;i<N;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			sum[i]=1;
		}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			sum[i*prime[j]]=sum[i]+sum[prime[j]];
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	init();
	int l,r;
	cin>>l>>r;
	int ans=0;
	for(int i=l;i<=r;i++){
		if(!vis[sum[i]])ans++;
	}
	cout<<ans;
}

