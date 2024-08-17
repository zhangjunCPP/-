#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
bool vis[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],vis[i]=false;
	if(n==1){cout<<"0\n";return;}
	int ans=0;
	int sum2=0;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int sum=0;
		int now=a[i];
		while(now!=i){/*cout<<now<<" ";*/vis[now]=true;now=a[now];sum++;}
//		cout<<now<<"\n";
		sum++;
		vis[i]=true;
		if(sum==1)continue;
		else if(sum==2)sum2++;
		else if(sum==3)ans++;
		else if(sum==4)ans++;
		else{
			if(sum%3==1)ans+=sum/3;
			else if(sum%3==2)ans+=sum/3,sum2++;
			else ans+=sum/3;
		}
	}
	ans+=(sum2+1)/2;
	cout<<ans<<"\n";
	
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}