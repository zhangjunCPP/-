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
	// for(int i=1;i<=n;i++)cout<<Min[i]<<" ";
	// cout<<"\n";
	int ans=0;
	int las=0;//剩下的
	for(int i=1;i<=n;i++){
		// cout<<"i="<<i<<" last="<<las<<"\n";
		ans+=m*las;
		int tmp=min(las,d[i]);
		las-=tmp,d[i]-=tmp;
		ans+=d[i]*p[i];
		// if(i<n&&p[i]+m<p[i+1]){
		// 	tmp=min(V,d[i+1])-las;
		// 	las+=tmp;
		// 	ans+=tmp*p[i];
		// }
		if(i<n){
			tmp=max(0ll,min(V,sum[Min[i]]-sum[i])-las);
			// cout<<"tmp="<<tmp<<"\n";
			las+=tmp;
			ans+=tmp*p[i];
		}
		// cout<<"i="<<i<<" ans="<<ans<<"\n------\n";
	}
	cout<<ans;
}
/*
3 1 2
2 1 2
3 6 6
*/
/*
说实话，感觉这道题很像之前做过的一道网络流题，但看数据范围，不太能做
*/
/*
贪心的想，如果没有存储开销的话，我一定尽可能地在价格低点买入
如果有存储开销，相当于这一天额外进货单价加了m，这样就没有存储开销了
*/
