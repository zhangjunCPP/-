#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int fa[N];
int find(int x){return fa[x]!=x?fa[x]=find(fa[x]):x;}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fy]=fx;
}
int prime[N],cnt;
bool vis[N];
int Min[N];
void init(){
	Min[1]=1;
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++cnt]=i,Min[i]=cnt;
		for(int j=1;j<=cnt&&prime[j]*i<N;j++){
			vis[prime[j]*i]=true;
			Min[prime[j]*i]=j;
			if(i%prime[j]==0)break;
		}
	}
}
int a[N];
vector<int> G[N];
void solve(){
	int n,k;
	cin>>n>>k;
	int sum=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x==1)sum++;
		a[i-1]=a[n+i-1]=x;
	}
	int ans=0;
	ans+=n*sum;
	n*=2;
	for(int i=1;i<n;i++)fa[i]=i;
	map<int,bool> mp;
	for(int i=1;i<n;i++){
		int tmp=a[i];
		while(tmp>1){
			mp[Min[tmp]]=true;
			G[Min[tmp]].push_back(i);
			int x=prime[Min[tmp]];
			while(tmp%x==0)tmp/=x;
		}
	}
	for(auto i:mp){
		int last=0;
		for(int j:G[i.first]){
			if(last&&j-last<=k)merge(j,last);
			last=j;
		}
		G[i.first].clear();
	}
	for(int i=1;i<n;i++)if(a[i]!=1&&fa[i]==i)ans++;
	cout<<ans<<"\n";
}
signed main(){
	init();
	int T;
	cin>>T;
	while(T--)solve();
}