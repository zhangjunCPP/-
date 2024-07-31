#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e9;
int p[N];
vector<pair<int,int>>ans;
void solve(int x,int y) {
	if(x<=y) {
		y+=2;
		int tmp1=p[x],tmp2=p[x+1];
		for(int i=x+2;i<=y;i++)p[i-2]=p[i];
		p[y+1]=tmp1,p[y+2]=tmp2;
	}
	else {
		int tmp1=p[x],tmp2=p[x+1];
		for(int i=x-1;i>y;i--)p[i+2]=p[i];
		p[y+1]=tmp1,p[y+2]=tmp2;
	}
}
signed main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n-2;++i) {
		int pos=1;
		for(int j=1;j<=n;++j)if(p[j]==i)pos=j;
		if(pos==i) continue;
		if(pos==n) {
			ans.push_back({n-1,n-3});
			solve(n-1,n-3);
			ans.push_back({n-1,i-1});
			solve(n-1,i-1);
		}
		else {
			ans.push_back({pos,i-1});
			solve(pos,i-1);
		}
	}
	if(p[n-1]>p[n]){puts("No");return 0;}
	puts("Yes");
	cout<<ans.size()<<"\n";
	for(auto i:ans)cout<<i.first<<" "<<i.second<<"\n";
}