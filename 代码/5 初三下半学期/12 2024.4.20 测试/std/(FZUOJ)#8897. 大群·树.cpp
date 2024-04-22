#include<bits/stdc++.h>
using namespace std;
int n,k,x,y,i,t,s[600001],w[600001],vis[600001],siz[600001];
long long ans,p[600001],q[600001];
struct node{int x,y;node(int a=0,int b=0){x=a;y=b;}};
vector<node>v[600001];
void link(int x,int y,int z){v[x].emplace_back(y,z);v[y].emplace_back(x,z);}
int dfs(int x,int y){
	siz[x]=1;
	for(node i:v[x])if(i.x!=y&&!vis[i.x])siz[x]+=dfs(i.x,x);
	return siz[x];
}
int dfs(int x,int y,int z){
	int c=-1;
	for(node i:v[x])if(i.x!=y&&!vis[i.x])c=max(c,dfs(i.x,x,z));
	if(c==-1&&siz[x]*2>=z)c=x;
	return c;
}
void solve(int x,int y,int z){
	s[z]+=w[x];t=max(t,z);
	for(node i:v[x])if(i.x!=y&&!vis[i.x])solve(i.x,x,z+1);
}
void calc(int x,int r,int y,int z,int f){
	p[x]+=f*s[min(t,k-z)];q[r]+=f*s[min(t,k-z)];
	for(node i:v[x])if(i.x!=y&&!vis[i.x])calc(i.x,i.y,x,z+1,f);else if(i.x!=y)q[i.y]+=f*s[min(t,k-z-1)];
}
void add(int p,int q,int x,int y,int f){
	t=0;solve(p,x,y);
	for(int i=1;i<=t;i++)s[i]+=s[i-1];
	calc(p,q,x,y,f);
	for(int i=0;i<=t;i++)s[i]=0;
}
void solve(int x){
	x=dfs(x,0,dfs(x,0));
	vis[x]=1;add(x,0,0,0,1);
	for(node i:v[x])if(!vis[i.x])add(i.x,i.y,x,1,-1);
	for(node i:v[x])if(!vis[i.x])solve(i.x);
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout); 
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	for(i=1;i<=n;i++)w[i]=1;
	for(i=1;i<n;i++)cin>>x>>y,link(x,n+i,i),link(y,n+i,n+i-1);
	solve(1);
	for(i=1;i<n*2;i++)ans+=p[i]*(p[i]-1)*(p[i]-2)/6;
	for(i=1;i<n*2-1;i++)ans-=q[i]*(q[i]-1)*(q[i]-2)/6;
	cout<<ans<<"\n";
}
