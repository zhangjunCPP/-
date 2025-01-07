#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
map<int,int> mp;
string s1,s2;
int a[N];
void solve(){
	mp.clear();
	int n,k;
	cin>>n>>k;
	cin>>s1>>s2;
	int cnt=0;
	for(int i=0;i<n;i++) if(!mp.count(s1[i])) mp[s1[i]]=cnt++;
	for(int i=0;i<n;i++) a[i]=mp[s1[i]];
	int ans=0;
	for(int i=0;i<(1<<cnt);i++){
		if(__builtin_popcount(i)<=k){
			int tmp=0;
			int len=0;
			for(int j=0;j<n;j++){
				if(s1[j]==s2[j]||(i&(1<<a[j]))) len++;
				else {
					tmp+=len*(len+1)/2;
					len=0;
				}
			}
			tmp+=len*(len+1)/2;
			len=0;
			ans=max(ans,tmp);
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)solve();
}