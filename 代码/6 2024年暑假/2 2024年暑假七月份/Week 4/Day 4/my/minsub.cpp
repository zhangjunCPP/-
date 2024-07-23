#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
map<vector<int>,int>mp;
int dfs(int l,int r) {
	if(l>=r)return 0;
	if(l+1==r)return a[l]==a[r]?2:1;
	vector<int>tmp;
	for(int i=l;i<=r;i++)tmp.push_back(a[i]);
	if(mp.count(tmp))return mp[tmp];
	int Max=0;
	for(int i=l;i<r;i++) {
		int tmp1=a[i],tmp2=a[i+1];
		int Min=min(tmp1,tmp2);
		a[i]-=Min;
		a[i+1]-=Min;
		if((!a[i])&&(!a[i+1]))Max=max(Max,dfs(l,i-1)+dfs(i+2,r)+2);
		else if(!a[i])Max=max(Max,dfs(l,i-1)+dfs(i+1,r)+1);
		else Max=max(Max,dfs(l,i)+dfs(i+2,r)+1);
		a[i]=tmp1,a[i+1]=tmp2;
	}
	mp[tmp]=Max;
	return Max;
}
vector<int>tmp;
int main() {
	freopen("minsub.in","r",stdin);
	freopen("minsub.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],tmp.push_back(a[i]);
	sort(tmp.begin(),tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()),tmp.end());
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp.begin(), tmp.end(),a[i])-tmp.begin()+1;
	cout<<dfs(1,n);
}
