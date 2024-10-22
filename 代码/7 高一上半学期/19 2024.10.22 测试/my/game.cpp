#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int x[N];
int nex[N];
int rev[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>x[i];
	int ans=0;
	nex[1]=1,rev[1]=1;
	for(int i=2;i<=n;i++){
		int fa;
		cin>>fa;
		nex[i]=nex[fa];
		rev[nex[i]]=i;
		nex[fa]=i;
		rev[nex[fa]]=fa;
		int _pre=x[fa];
		int _nex=x[nex[i]];
		if(x[i]>max(_pre,_nex))ans+=x[i]-max(_pre,_nex);
		else if(x[i]<min(_pre,_nex))ans+=min(_pre,_nex)-x[i];
		cout<<ans<<"\n";
	}
}
/*
发现计数器最少的一定无法被一起抬升，因此我们可以每次都加最少的，这样应该是最优的
考虑怎么维护这个东西
*/