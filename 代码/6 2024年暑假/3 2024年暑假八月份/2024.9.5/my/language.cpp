#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=1e5+10;
const ull p=1331;
ull pw[N];
ull Hash[N];
ull calc(int l,int r){return Hash[r]-Hash[l-1]*pw[r-l+1];}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	string s;
	cin>>s;
	int n=s.size();
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*p;
	for(int i=0;i<n;i++)Hash[i+1]=Hash[i]*p+s[i]-'a'+1;
	int q;
	cin>>q;
	while(q--) {
		string t;
		cin>>t;
		int m=t.size();
		ull Hash_t=0;
		for(int i=0;i<m;i++)Hash_t=Hash_t*p+t[i]-'a'+1;
		int ans=0;
		for(int i=1;i<=n-m+1;i++)if(calc(i,i+m-1)==Hash_t)ans++,i=i+m-1;
		cout<<ans<<"\n";
	}
}
