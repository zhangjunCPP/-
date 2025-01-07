#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int a,b,d;
	cin>>a>>b>>d;
	int c=a|b;
	int last=0;
	for(int i=30;i>=0;i--) if(d&(1<<i))last=i;
	int ans=0;
	for(int i=0;i<=30;i++){
		if((c&(1<<i))&&(!(ans&(1<<i)))){
			if(i<last){puts("-1");return;}
			ans+=d<<(i-last);
		}
	}
	cout<<ans<<"\n";
}
signed main() {
	int T;
	cin>>T;
	while(T--)solve();
}