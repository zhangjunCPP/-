#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,k;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dp[N];
void dfs(int u,int dad){
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		dfs(v,u);
	}
	int sum1=0,sum2=1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==dad) continue;
		if(dp[v]) sum1++;
		sum2+=dp[v];
	}
	if(sum2==k){dp[u]=0;return;}
	if(sum2>k) {cout<<"No";exit(0);}
	if(sum2<k) {dp[u]=sum2;return;}
	return;
}
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
}
signed main(){
	freopen("cut.in","r",stdin);
	freopen("cut.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<n;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
		add(v,u);
	}
	if(k==1) {cout<<"Yes";return 0;}
	if(n==k) {cout<<"Yes";return 0;}
	if(n%k!=0) {cout<<"No";return 0;}
	dfs(1,0);
	cout<<"Yes";
	return 0;
}
