#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
string s[N];
int i,j;
int main(){
	freopen("lihua.in","r",stdin);
	freopen("lihua.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(i=1;i<=n;++i) cin>>s[i];
	int q;
	cin>>q;
	string t;
	int ans;
	int siz1,siz2,SIZ;
	while(q--) {
		ans=0;
		cin>>t;
		siz1=t.size();
		for(i=1;i<=n;i++) {
			ans++;
			siz2=s[i].size();
			SIZ=min(siz1,siz2);
			for(j=0;j<SIZ;j++) {
				if(t[j]==s[i][j]) ans++;
				else break;
			}
			if(j==SIZ&&siz1==siz2) break;
		}
		cout<<ans<<"\n";
	}
}