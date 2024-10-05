#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
int a[N],b[N];
int deg[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		deg[x]++,deg[y]++;
		if(deg[x]>2||deg[y]>2){cout<<"No";return 0;}
		int fx=find(x),fy=find(y);
		if(fx==fy){cout<<"No";return 0;}
		fa[fx]=fy;
	}
	cout<<"Yes";
}