#include<bits/stdc++.h>
#define int long long
using namespace std;
int random(int l,int r){return rand()%(r-l+1)+l;}
int qpow(int x,int y,int p){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%p;
		y>>=1;
		x=x*x%p;
	}
	return ans%p;
}
int f1(int x,int y,int z,int n,int p){return (qpow(x,3*n,p)+qpow(y,3*n,p)+qpow(z,3*n,p))%p;}
int f2(int x,int y,int z,int n,int p){return (x+y+z)%p*(qpow(x,1*n,p)+qpow(y,1*n,p)+qpow(z,1*n,p))%p*(qpow(x,2*n,p)+qpow(y,2*n,p)+qpow(z,2*n,p))%p;}
int inv(int x,int p){return qpow(x,p-2,p);}
int ans[4];
void solve(){
	int n,p;
	cin>>n>>p;
	while(true){
		ans[0]=random(1,p-3);ans[1]=random(ans[0]+1,p-2);ans[2]=random(ans[1]+1,p-1);
		int k=f1(ans[0],ans[1],ans[2],n,p)*inv(f2(ans[0],ans[1],ans[2],n,p),p)%p;
		ans[0]=ans[0]*k%p;ans[1]=ans[1]*k%p;ans[2]=ans[2]*k%p;
		sort(ans,ans+3);
		if(ans[0]&&ans[0]!=ans[1]&&ans[1]!=ans[2]&&ans[0]!=ans[2]){
			cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<"\n";
			break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	srand(time(NULL));
	int T;
	cin>>T;
	while(T--)solve();
}