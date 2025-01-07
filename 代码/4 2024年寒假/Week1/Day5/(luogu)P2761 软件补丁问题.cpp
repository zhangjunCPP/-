#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m;
int b1[N],b2[N];
int f1[N],f2[N];
int w[N];
int dis[N];
bool vis[N];
void solve(){
	queue<int> q;
	int s=(1<<n)-1,t=0;
	memset(dis,0x3f,sizeof dis);
	dis[s]=0;
	q.push(s);
	vis[s]=true;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=1;i<=m;i++){
			if( ((u&b1[i])==b1[i]) && ((u&b2[i])==0) ) {
				int v=((u|f1[i])^f1[i])|f2[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					if(!vis[v]) q.push(v),vis[v]=true;
				}
			}
		}
	}
	if(dis[t]==0x3f3f3f3f) dis[t]=0;
	cout<<dis[t];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>w[i];
		string s1,s2;
		cin>>s1>>s2;
		for(int j=0;j<n;j++){
			if(s1[j]=='+') b1[i]|=(1<<j);
			if(s1[j]=='-') b2[i]|=(1<<j);
			if(s2[j]=='-') f1[i]|=(1<<j);
			if(s2[j]=='+') f2[i]|=(1<<j);
		}
	}
	solve();
}