#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
map<int,int> a[N];
int nex[N];
long long dp[N];
int s[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=1;i<=n;i++){
        nex[i]=i;
        int tmp=a[nex[i-1]][s[i]];
        if(tmp)nex[i]=nex[tmp-1],dp[i]=dp[tmp-1]+1;
        a[nex[i]][s[i]]=i;
    }
    long long ans=0;
    for(int i=1;i<=n;i++) ans+=dp[i];
    cout<<ans;
	return 0;
}