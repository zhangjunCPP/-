#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=2e5+10;
int a[N],tmp[N];
const ull p=1331;
ull fac[N];
vector<int>G[N];
map<ull,int> mp;
ull Hash[N];
int sum[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	fac[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*p;
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	int tot=n;
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;
	int l=0;
	mp[0]++;
	ull now=0;
	long long ans=0;
	for(int i=1;i<=n;i++){
		G[a[i]].push_back(i);
		if(G[a[i]].size()>k)while(l<G[a[i]][G[a[i]].size()-1-k])mp[Hash[l]]--,l++;
		now-=sum[a[i]]*fac[a[i]];
		sum[a[i]]++;
		sum[a[i]]%=k;
		now+=sum[a[i]]*fac[a[i]];
		ans+=mp[now];
		Hash[i]=now;mp[now]++;
	}
	cout<<ans;
}