#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int q[N],v[N];
int vis[N];
int flag1[N],flag2[N];
signed main() {
	int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++)cin>>q[i]>>v[i];
	int now1=1,now2=1;
	int ans=0;
	while (s>=1&&s<=n){
		if(q[s]){
			if(!vis[s]&&now1>=v[s])vis[s]=1,flag1[s]=now1,flag2[s]=now2,ans++;
			else if(flag1[s]==now1&&flag2[s]==now2)break;
		}
		else now1+=v[s],now2*=-1;
		s+=now1*now2;
	}
	cout << ans;
	return 0;
}
