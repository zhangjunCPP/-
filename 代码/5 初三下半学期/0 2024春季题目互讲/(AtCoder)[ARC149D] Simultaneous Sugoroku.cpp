#include <bits/stdc++.h>

using namespace std;
const int N=1e6+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int pos[N],stop[N];
int x[N],d[N];
void dfs(int u){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(stop[u])stop[v]=stop[u];
		else pos[v]=-pos[u];
		dfs(v);
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i];
	for(int i=1;i<=m;i++)cin>>d[i];
	int l=1,r=1e6;
	int p=0;
	for(int i=1;i<=m;i++){
		if(l+p>0)p-=d[i];
		else p+=d[i];
		int mid=-p;
		if(l<=mid&&r>=mid){
			stop[mid]=i;
			if(mid-l<r-mid){
				for(int j=l;j<mid;j++)add(mid*2-j,j);
				l=mid+1;
			}
			else{
				for(int j=mid+1;j<=r;j++)add(mid*2-j,j);
				r=mid-1;
			}
		}
	}
	for(int i=l;i<=r;i++){
		if(!stop[i])pos[i]=i+p;
		dfs(i);
	}
	for(int i=1;i<l;i++)if(stop[i])dfs(i);
	for(int i=1e6;i>r;i--)if(stop[i])dfs(i);
	for(int i=1;i<=n;i++){
		if(stop[x[i]])cout<<"Yes "<<stop[x[i]]<<"\n";
		else cout<<"No "<<pos[x[i]]<<"\n";
	}
}