#include<bits/stdc++.h>
using namespace std;
int n,m;
map<int,int> mp;
bool check(int x) {
	set<pair<int,int>>st;
	for(auto i:mp)st.emplace(-abs(i.second),i.first);
	while(st.size()) {
		auto now=st.begin();
		st.erase(now);
		if(-now->first<x)break;
		int a=now->second;
		mp[(a+1)%m]+=mp[a]/x;
		mp[a]%=x;
		st.emplace(-abs(mp[a]),a);
		st.emplace(-abs(mp[(a+1)%m]),(a+1)%m);
	}
	if(mp.begin()->second%(x-1))return false;
	int tmp=mp.begin()->second/(x-1);
	for(auto i:mp)if(i.second!=(x-1)*tmp)return false;
	return true;
}
int cl;
void solve() {
	mp.clear();
	cin>>n>>m;
	int sum=0;
	for(int i=1;i<=n;i++) {
		int c,a;
		cin>>c>>a;
		mp[a%m]-=c;
		mp[(a+1)%m]+=c;
		sum+=c;
	}
	int ans=(sum%m==0);
	bool flag=true;
	for(auto i:mp)if(i.second!=0){flag=false;break;}
	if(flag){cout<<"-1\n";return;}
	map<int,int> tmp=mp;
	for(int i=n;i>1;i--) {
		if(clock()-cl>800000)break;
		ans+=check(i),mp=tmp;
	}
	cout<<ans<<"\n";
}
int main() {
	cl=clock();
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}