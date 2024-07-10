#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n;
int a[N];
vector<int>G[N];

int fa[N];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fx]=fy;
}

int ans[N];
bool vis[N];
void clear() {
	for(int i=1;i<=n;i++)G[i].clear(),vis[i]=false;
}
vector<int>S;
void dfs(int u){
	if(vis[u])return;
	vis[u]=true;
	S.push_back(u);
	dfs(ans[u]);
}
void solve(){
	clear();
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		G[a[i]].push_back(i);
	}
	int tmp=0;
	for(int i=1;i<=n;i++)tmp+=(G[i].size()&1);
	if(tmp>1){cout<<"NO\n";return;}
	int mid=(n+1)>>1;
	if(n&1&&G[a[mid]].size()==1){cout<<"NO\n";return;}
	int l=1,r=1;
	for(int i=1;i<=n;i++){
		int pos=0;
		if(G[i].size()&1){
			for(int j:G[i])if(j!=mid){pos=j;break;}
			ans[mid]=pos;
		}
		for(int j:G[i]){
			if(j!=pos){
				if(l==r)ans[l]=j,l++;
				else ans[n-r+1]=j,r++;
			}
		}
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		S.clear();
		dfs(i);
		for(int j=1;j<S.size();j++)merge(S[0],S[j]);
	}
	for(int i=1;i<=n/2;i++){
		if(find(i)!=find(n-i+1)){
			swap(ans[i],ans[n-i+1]);
			merge(i,n-i+1);
		}
	}
	for(int i=2;i<=n/2;i++){
		if(find(i)!=find(i-1)){
			swap(ans[i],ans[i-1]);
			swap(ans[n-i+1],ans[n-i+2]);
			swap(ans[i],ans[n-i+1]);
			merge(i,i-1);
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<'\n';
}

signed main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}