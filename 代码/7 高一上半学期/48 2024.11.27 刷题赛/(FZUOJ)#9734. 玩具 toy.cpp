#include<bits/stdc++.h>
using namespace std;
const int N=3e6+10;
int G[N],tot;
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int a,b,n;
	cin>>b>>a>>n;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++)if(s[i-1]=='1')G[++tot]=i;
	int now1=a,now2=b;
	long long ans=0;
	while(now1<n){
		while(now1-a+1<G[now2-b+1]&&now1<n)now1++,ans++;
		if(G[now2+1]>now1){
			puts("IMPOSSIBLE");
			return 0;
		}
		while(now2<n&&G[now2+1]<=now1)now2++;
		ans+=b;
	}
	cout<<ans;
}