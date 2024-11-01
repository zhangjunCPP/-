#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+7;
int x[N],y[N];
pair<int,int> a[N];
int cnt;
int tmp[N],tot;
int tree[N];
int lowbit(int x){return x&(-x);}
void add(int x,int val){for(int i=x;i<=tot;i+=lowbit(i))tree[i]=(tree[i]+val)%mod;}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans=(ans+tree[i])%mod;
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>x[i];
	for(int i=1;i<=m;i++)cin>>y[i];
	for(int i=1;i<=n;i++){
		if(x[i]<y[1])continue;
		if(x[i]>y[m])break;
		int pos=lower_bound(y+1,y+m+1,x[i])-y;
		a[++cnt]={x[i]-y[pos-1],y[pos]-x[i]};
		tmp[++tot]=y[pos]-x[i];
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=cnt;i++)a[i].second=lower_bound(tmp+1,tmp+tot+1,a[i].second)-tmp;
	sort(a+1,a+cnt+1,[](const pair<int,int>&s,const pair<int,int>&t){
		if(s.first==t.first)return s.second>t.second;
		return s.first<t.first;
	});
	cnt=unique(a+1,a+cnt+1)-a-1;
	int ans=1;
	for(int i=1;i<=cnt;i++){
		int s=query(a[i].second-1)+1;
		ans=(ans+s)%mod;
		add(a[i].second,s);
	}
	cout<<ans;
}