#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
bool dp[N][N];
int a[N];
int s[N];
int L[N],R[N];
bool ans[N];
int highbit(int x){return (x!=(1ll<<62))?(1ll<<(63-__builtin_clzll(x))):(1ll<<62);}
int sum(int l,int r){return (s[r]^s[l-1])?(s[r]^s[l-1]):(1ll<<62);}
void solve(){
	int n;
	cin>>n;
	memset(L,0,sizeof L);
	memset(R,0,sizeof R);
	memset(ans,false,sizeof ans);
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n==1){cout<<"1\n";return;}
	for(int i=1;i<=n;i++)s[i]=s[i-1]^a[i];
	L[1]|=highbit(sum(1,n)),R[n]|=highbit(sum(1,n));
	for(int len=n-1;len;len--){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			int tmp=sum(i,j);
			int flag=(tmp&L[i])|((1ll<<62)&L[i])|(tmp&R[j])|((1ll<<62)&R[j]);
			if(flag){
				L[i]|=highbit(tmp),R[j]|=highbit(tmp);
				if(len==1)ans[i]=true;
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i];
	cout<<"\n";
	return;
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
}