#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e9;
int p[N];
void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	int ans=0;
	int Min=INF;
	for(int i=n;i;i--)if(p[i]<Min)Min=p[i],ans++;
	cout<<ans<<"\n";
}
signed main() {
	int T;
	cin>>T;
	while(T--)solve();
}