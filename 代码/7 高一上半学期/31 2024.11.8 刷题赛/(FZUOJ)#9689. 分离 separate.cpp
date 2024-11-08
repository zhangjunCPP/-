#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,INF=2e9;
int a[N];
int suf[N];
bool vis[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	suf[n+1]=INF;
	for(int i=n;i;i--)suf[i]=min(suf[i+1],a[i]);
	basic_string<int> ans1,ans2;
	int first=INF;
	for(int i=1;i<=n;i++)vis[i]=false;
	for(int i=1;i<=n;i++){
		if(a[i]==suf[i]&&a[i]<=first)vis[i]=true,ans1.push_back(a[i]);
		else if(first==INF)first=a[i];
	}
	for(int i=1;i<=n;i++)if(!vis[i])ans1.push_back(a[i]);
	first=INF;
	for(int i=1;i<=n;i++)vis[i]=false;
	for(int i=1;i<=n;i++){
		if(a[i]==suf[i]&&a[i]<first)vis[i]=true,ans2.push_back(a[i]);
		else if(first==INF)first=a[i];
	}
	for(int i=1;i<=n;i++)if(!vis[i])ans2.push_back(a[i]);
	auto ans=ans1;
	if(ans1>ans2)ans=ans2;
	for(int it:ans)cout<<it<<" ";
	cout<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}