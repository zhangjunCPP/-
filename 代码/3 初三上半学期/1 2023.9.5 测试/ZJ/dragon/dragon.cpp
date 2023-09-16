#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e6+10;
int a[N];
int cnt[N];
bool s[1005][1005];
signed main(){
	freopen("dragon.in","r",stdin);
	freopen("dragon.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,K,q;
	cin>>n>>K>>q;
	for(int i=1;i<=n;i++) cin>>a[i]; 
	if(K==1){
		while(q--){
			int l,r;
			cin>>l>>r;
			cout<<(r-l+1)*(r-l+1+1)/2<<"\n";
		}
		return 0;
	}
	else{
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				bool flag=true;
				for(int k=i;k<=j;k++) cnt[a[k]]=0;
				for(int k=i;k<=j;k++) cnt[a[k]]++;
				for(int k=i;k<=j;k++)if(cnt[a[k]]%K!=0) flag=false;
				s[i][j]=flag;
			}
		}
		while(q--){
			int l,r;
			cin>>l>>r;
			int ans=0;
			for(int i=l;i<=r;i++){
				for(int j=i;j<=r;j++){
					ans+=s[i][j];
				}
			}
			cout<<ans<<"\n";
		}
	}
	

	return 0;
}


