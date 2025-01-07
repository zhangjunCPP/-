#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int a[N];
int tmp[N];
int ans[N];
bool vis[N];
int sta[N],top;
int dfs(int k){
	if(k>n){
		for(int i=1;i<=2*n;i++)ans[i]=tmp[a[i]];
		top=0;
		for(int i=1;i<=n;i++)vis[i]=false;
		for(int i=1;i<=2*n;i++){
			if(ans[i]==2)continue;
			if(!vis[a[i]]){
				sta[++top]=a[i];
				vis[a[i]]=true;
			}
			else{
				if(sta[top]!=a[i])return 0;
				else top--;
			}
		}
		if(top)return 0;
		top=0;
		for(int i=1;i<=n;i++)vis[i]=false;
		for(int i=1;i<=2*n;i++){
			if(ans[i]==1)continue;
			if(!vis[a[i]]){
				sta[++top]=a[i];
				vis[a[i]]=true;
			}
			else{
				if(sta[top]!=a[i])return 0;
				else top--;
			}
		}
		if(top)return 0;

		for(int i=1;i<=2*n;i++)cout<<ans[i];
		cout<<"\n";
		return 1;
	}
	tmp[k]=1;
	if(dfs(k+1))return 1;
	tmp[k]=2;
	if(dfs(k+1))return 1;
	return 0;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n*2;i++)cin>>a[i];
	if(!dfs(1))cout<<"-1\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}