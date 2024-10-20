#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
vector<pair<int,int>> v[N];
signed main(){	
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int c,w,f;
		cin>>c>>w>>f;
		if(!c||!f)continue;
		v[w].push_back({f,c});
	}
	for(int i=0;i<m;i++){
		sort(v[i].begin(),v[i].end());
		while(!v[i].empty()){
			if(v[i].back().second>1){//最后一个能组成更大的
				v[i+1].push_back({v[i].back().first,v[i].back().second/2});
				v[i].back().second-=v[i].back().second/2*2;
				if(!v[i].back().second)v[i].pop_back();
			}
			else if(v[i].size()>1){
				v[i+1].push_back({v[i].back().first,1});
				v[i].pop_back();
				v[i].back().second--;
				if(!v[i].back().second)v[i].pop_back();
			}
			else break;
		}
		if(!v[i].empty())v[i+1].push_back(v[i].back()),v[i].pop_back();
	}
	int ans=0;
	for(auto i:v[m])ans+=i.first*i.second;
	cout<<ans;
}