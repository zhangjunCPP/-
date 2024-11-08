#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		int fx=find(u),fy=find(v);
		if(fx!=fy)fa[fx]=fy;
	}
	int ans=0;
	for(int i=1;i<=n;i++)if(fa[i]!=i)ans++;
	cout<<ans;
}