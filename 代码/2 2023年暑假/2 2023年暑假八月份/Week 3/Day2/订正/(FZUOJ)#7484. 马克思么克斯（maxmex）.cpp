#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int a[N];
vector<int> s[N];
vector<pair<int,int>> v[N];

bool cmp1(const pair<int,int>&x,const pair<int,int>&y){
	if(x.first!=y.first) return x.first<y.first;
	else return x.second<y.second;
}

bool cmp2(const pair<int,int>&x,const pair<int,int>&y){
	if(x.second!=y.second) return x.second>y.second;
	else return x.first>y.first;
}

int ans[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[a[i]].push_back(i);
		if(a[i]==0) v[0].push_back({i,i});
	}
	for(int i=0;i<=n;i++){
		if(!s[i+1].size()) break;

		sort(v[i].begin(),v[i].end(),cmp1);
		int last=0;//去重
		for(auto now:v[i]){
			int l=now.first,r=now.second;
			if(l==last) continue;
			last=l;
			auto rr=lower_bound(s[i+1].begin(),s[i+1].end(),l);
			if(rr!=s[i+1].end()) v[i+1].push_back({l,max(r,*rr)});
		}

		sort(v[i].begin(),v[i].end(),cmp2);
		last=0;
		for(auto now:v[i]){
			int l=now.first,r=now.second;
			if(r==last) continue;
			last=r;
			auto ll=lower_bound(s[i+1].begin(),s[i+1].end(),r);
			if(ll!=s[i+1].begin()) v[i+1].push_back({min(l,*(--ll)),r});
		}
	}
	for(int i=0;i<=n;i++){
		for(auto now:v[i]){
			int l=now.first,r=now.second;
			ans[r-l+1]=max(ans[r-l+1],i+1);
		}
	}
	for(int i=1;i<=n;i++) ans[i]=max(ans[i],ans[i-1]);

	int q;
	cin>>q;
	while(q--){
		int k;
		cin>>k;
		cout<<ans[k]<<"\n";
	}
}