#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int deg[N];
unordered_set<int> G[N];
int main(){
	int n,q;
	cin>>n>>q;
	int sum=n;
	while(q--){
		int opt;
		cin>>opt;
		if(opt==1){
			int u,v;
			cin>>u>>v;
			G[u].insert(v);
			G[v].insert(u);
			if(deg[u]==0)sum--;
			if(deg[v]==0)sum--;
			deg[u]++,deg[v]++;
		}
		else{
			int v;
			cin>>v;
			for(int u:G[v]){
				G[u].erase(v);
				if(deg[u]==1)sum++;
				deg[u]--;
			}
			G[v].clear();
			if(deg[v])deg[v]=0,sum++;
		}
		cout<<sum<<"\n";
	}
	return 0;
}