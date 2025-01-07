#include<bits/stdc++.h>
#define int long long
using namespace std;
set<int>mp;
int n,k;
void calc(int x){
	for(int i=1;i*i<=x;i++){
		if(x%i==0){
			if(i/2+1>=k&&i%2==0)mp.insert(i);
			int j=x/i;
			if(j/2+1>=k&&j%2==0)mp.insert(j);
		} 
	}
}
void solve(){
	mp.clear();
	cin>>n>>k;
	calc(n-k);
	calc(n+k-2);
	cout<<mp.size()<<endl;
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}
