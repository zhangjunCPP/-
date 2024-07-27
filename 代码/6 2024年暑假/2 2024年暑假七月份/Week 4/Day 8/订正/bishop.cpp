#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>> ans;
int main(){
	freopen("bishop.in", "r", stdin);
	freopen("bishop.out", "w", stdout);
	int n,m;
	cin>>n>>m;
	bool flag=false;
	if(n<m)swap(n,m),flag=true;
	if(n==m){
		cout<<max(1,2*n-2)<<"\n";
		for(int i=1;i<=m;i++)cout<<"1 "<<i<<"\n";
		for(int i=2;i<m;i++)cout<<n<<" "<<i<<"\n";
		return 0;
	}
	for(int i=1;i<=m;i++)ans.emplace_back(1,i);
	for(int i=1;i<=m;i++)ans.emplace_back(n,i);
	if(m&1)for(int i=m/2+2;i<=n-m/2-1;i++)ans.emplace_back(i,m/2+1);
	else{
		for(int i=m/2+2;i<=n-m/2-1;i+=2){
			ans.emplace_back(i,m/2);
			ans.emplace_back(i,m/2+1);
		}
	}
	cout<<ans.size()<<"\n";
	for(auto i:ans){
		if(flag)cout<<i.second<<" "<<i.first<<"\n";
		else cout<<i.first<<" "<<i.second<<"\n";
	}
}