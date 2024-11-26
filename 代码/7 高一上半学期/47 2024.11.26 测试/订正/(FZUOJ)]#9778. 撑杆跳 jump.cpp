#include<bits/stdc++.h>
using namespace std;
const int N=300+10;
struct node{
	int v,c;
}a[N];
unordered_map<int,int> mp;
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].v;
	for(int i=1;i<=n;i++)cin>>a[i].c;
	mp.clear();
	for(int i=1;i<=n;i++){
		auto tmp=mp;
		for(auto it:tmp){
			int GCD=__gcd(it.first,a[i].v);
			if(!mp.count(GCD))mp[GCD]=it.second+a[i].c;
			else mp[GCD]=min(mp[GCD],it.second+a[i].c);
		}
		if(!mp.count(a[i].v))mp[a[i].v]=a[i].c;
		else mp[a[i].v]=min(mp[a[i].v],a[i].c);
	}
	if(!mp.count(1))cout<<"-1\n";
	else cout<<mp[1]<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
