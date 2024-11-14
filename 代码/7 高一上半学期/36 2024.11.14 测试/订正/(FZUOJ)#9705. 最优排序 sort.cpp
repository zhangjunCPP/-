#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
bool vis[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)vis[i]=false;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n==1){cout<<"0\n";return;}
	int cnt2=0,cnt3=0;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int tot=0;
		int now=a[i];
		do{
			tot++;
			vis[now]=true;
			now=a[now];
		}while(now!=a[i]);
		if(tot==1)continue;
		if(tot==2)cnt2++;
		else if(tot==3)cnt3++;
		else{
			ans+=tot/3;
			tot%=3;
			if(tot==2)cnt2++;
		}
	}
	cout<<ans+(cnt2+1)/2+cnt3<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}