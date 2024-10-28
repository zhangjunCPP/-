//AGC026B
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a<b||d<b){cout<<"No\n";return;}
	int gcd=__gcd(b,d);
	cout<<((a-c-1)/gcd<=(a-b)/gcd?"Yes\n":"No\n");
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}