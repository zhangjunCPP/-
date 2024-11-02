#include<bits/stdc++.h>
using namespace std;
const int N=40+10,mod=2000019;
int a[N];
int calc(int x){
	int sum=0;
	while(x){
		if(x%10==4)sum++;
		x/=10;
	}
	return sum;
}
unordered_map<int,int> mp,tmp;
int main(){
	freopen("four.in","r",stdin);
	freopen("four.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	mp[0]=1;
	for(int i=1;i<=n;i++){
		tmp=mp;
		for(auto it:tmp){
			mp[it.first+a[i]]+=it.second;
			mp[it.first+a[i]]%=mod;
		}
	}
	int ans=0;
	for(auto it:mp){
		ans+=calc(it.first)*it.second%mod;
		ans%=mod;
	}
	cout<<ans;
}