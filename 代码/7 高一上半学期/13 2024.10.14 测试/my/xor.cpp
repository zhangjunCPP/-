#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5000+10;
const int mod=998244353;
const int INF=1e18;
int a[N];
signed main(){
	int n,x;
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int S=1;S<(1<<n);S++){
		bool flag=true;
		for(int i=1;i<=n;i++){
			if((S>>(i-1))&1){
				for(int j=1;j<=n;j++){
					if((S>>(j-1))&1&&i!=j){
						if((a[i]^a[j])>x){flag=false;goto sb;}
					}
				}
			}
		}
		sb:;
		ans+=flag;
	}
	cout<<ans;
}