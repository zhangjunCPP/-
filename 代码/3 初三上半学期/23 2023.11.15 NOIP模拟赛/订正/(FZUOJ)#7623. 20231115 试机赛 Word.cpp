#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int n,k;
	cin>>n>>k;
	if(k==0) {
		cout<<0<<"\n";
		for(int i=1;i<=n;i++) cout<<"0 ";
		return 0;
	} 
	cout<<(n+1)/2*((n+1)/2+(n+1)%2)<<"\n";
	for(int i=1;i<=k-1;i++) cout<<"1 ";
	int tmp=k+(n-k+1)/2;
	for(int i=k;i<=n;i++)cout<<(i==tmp)<<" ";
	return 0;

