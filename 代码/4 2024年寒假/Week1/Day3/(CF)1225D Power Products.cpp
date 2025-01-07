#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=2e5+10;
int prime[N],cnt;
bool vis[N];
const int p=1331;
ull fac[N];
int id[N];
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*p;
	vis[1]= true;
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i,id[i]=cnt;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
map<ull,ull> mp;
signed main(){
	init(N-1);
	int n,k;
	cin>>n>>k;
	long long ans=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		ull hash1=0,hash2=0;
		for(int j=1;j<=cnt;j++){
			if(x==1)break;
			if(prime[j]*prime[j]>x) break;
			if(x%prime[j]==0){
				int tmp=0;
				while(x%prime[j]==0) x/=prime[j],tmp++;
				tmp%=k;
				if(tmp==0) continue;
				hash1+=tmp*fac[j];
				hash2+=(k-tmp)*fac[j];
			}
		}
		if(!vis[x]){
			hash1+=fac[id[x]];
			hash2+=(k-1)*fac[id[x]];
		}
		ans+=mp[hash2];
		mp[hash1]++;
	}
	cout<<ans;
}