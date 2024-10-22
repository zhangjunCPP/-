#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int d[N],p[N];
int sum[N];
int Min[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("ice.in","r",stdin);
	freopen("ice.out","w",stdout);
	int n,m,V;
	cin>>n>>m>>V;
	for(int i=1;i<=n;i++)cin>>d[i],sum[i]=sum[i-1]+d[i];
	for(int i=1;i<=n;i++)cin>>p[i];
	stack<int> sta;
	for(int i=1;i<=n;i++){
		while(!sta.empty()&&p[sta.top()]+m*(i-sta.top())>p[i]){
			Min[sta.top()]=i-1;
			sta.pop();
		}
		sta.push(i);
	}
	while(!sta.empty())Min[sta.top()]=n,sta.pop();
	int ans=0;
	int las=0;//剩下的
	for(int i=1;i<=n;i++){
		ans+=m*las;
		int tmp=min(las,d[i]);
		las-=tmp,d[i]-=tmp;
		ans+=d[i]*p[i];
		if(i<n){
			tmp=max(0ll,min(V,sum[Min[i]]-sum[i])-las);
			las+=tmp;
			ans+=tmp*p[i];
		}
	}
	cout<<ans;
}