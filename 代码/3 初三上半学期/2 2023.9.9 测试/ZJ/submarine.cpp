#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
int mp[N][N];
int r,c,m;
string s;
bool vis[N][N];
struct node{
	int i,j,id;
};
void calc(int i,int j){
	queue<node> q;
	q.push({i,j,0});
	while(!q.empty()){
		node now=q.front();
		q.pop();
		if(!mp[now.i][now.j]) continue;
		if(now.id>=m&&mp[now.i][now.j]) {
			vis[now.i][now.j]=1;
			continue;
		} 
		if(s[now.id]=='N') {if(mp[now.i-1][now.j]&&now.i-1>=1) q.push({now.i-1,now.j,now.id+1});}
		else if(s[now.id]=='E') {if(mp[now.i][now.j+1]&&now.j+1<=c) q.push({now.i,now.j+1,now.id+1});} 
		else if(s[now.id]=='S') {if(mp[now.i+1][now.j]&&now.i+1<=r) q.push({now.i+1,now.j,now.id+1});} 
		else if(s[now.id]=='W') {if(mp[now.i][now.j-1]&&now.j-1>=1) q.push({now.i,now.j-1,now.id+1});} 
		else if(s[now.id]=='?') {
			if(mp[now.i-1][now.j]&&now.i-1>=1) q.push({now.i-1,now.j,now.id+1});
			if(mp[now.i][now.j+1]&&now.j+1<=c) q.push({now.i,now.j+1,now.id+1});
			if(mp[now.i+1][now.j]&&now.i+1<=r) q.push({now.i+1,now.j,now.id+1});
			if(mp[now.i][now.j-1]&&now.j-1>=1) q.push({now.i,now.j-1,now.id+1});
		}
	}
}
signed main(){
	freopen("submarine.in","r",stdin);
	freopen("submarine.out","w",stdout); 
	cin>>r>>c>>m;
	for(int i=1;i<=r;i++){
		string tmp;
		cin>>tmp;
		for(int j=0;j<c;j++) {
			if(tmp[j]=='.') mp[i][j+1]=1;
			else mp[i][j+1]=0;
		}
	}
	cin>>s;
	for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)calc(i,j);			
	int ans=0;
	for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)ans+=vis[i][j];
	cout<<ans;
	
	return 0;
}

