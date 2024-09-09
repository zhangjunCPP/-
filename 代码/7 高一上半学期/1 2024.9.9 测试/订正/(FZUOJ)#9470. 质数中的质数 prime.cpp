#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
bool vis[N];
int prime[N],cnt;
int val[N];
int sum[N];
int main(){
	int l,r;
	cin>>l>>r;
	for(int i=l;i<=r;i++)val[i-l]=i;
	vis[0]=vis[1]=true;
	for(int i=2;i<N;i++){
		if(!vis[i]){
			prime[++cnt]=i;
			for(int j=i*((l-1)/i+1);j<=r;j+=i)while(val[j-l]%i==0)sum[j-l]++,val[j-l]/=i;
		}
		for(int j=1;j<=cnt&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
	int ans=0;
	for(int i=l;i<=r;i++)ans+=!vis[sum[i-l]+(val[i-l]!=1)];
	cout<<ans;
}