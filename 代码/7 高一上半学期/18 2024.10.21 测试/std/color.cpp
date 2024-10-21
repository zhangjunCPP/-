#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e6+5,mod=1e9+7;
int n,m,q,ct,fa[N];
ll pw[N];
int gf(int x){return x==fa[x]?x:fa[x]=gf(fa[x]);}
void un(int x,int y){x=gf(x),y=gf(y);if(x^y)fa[x]=y,ct--;}
int main() {

	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q,iota(fa+1,fa+2*(n+m)+1,1),pw[0]=1,ct=(n+m)*2;
	for(int i=1;i<=n+m;i++)pw[i]=pw[i-1]*2%mod;
	bool ok=1;cout<<pw[ct/2-1]<<'\n';
	while(q--) {
		int x,y,c;cin>>x>>y>>c;
		if(!ok){cout<<"0\n";continue;}
		un(x,y+n+c*(n+m)),un(x+n+m,y+n+(c^1)*(n+m));
		if(gf(x)==gf(x+n+m))ok=0,cout<<"0\n";
		else cout<<pw[ct/2-1]<<'\n';
	}
	return 0;
}
