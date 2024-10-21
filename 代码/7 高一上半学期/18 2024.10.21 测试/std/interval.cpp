#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=4e5+5;
int n,b[N],l[N],r[N],c[N];
void solve() {
	cin>>n,memset(c,0,sizeof(c));
	int L=1,R=1e9,num=0,ans=n;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i],b[++num]=l[i],b[++num]=r[i],L=max(L,l[i]),R=min(R,r[i]);
	sort(b+1,b+num+1),num=unique(b+1,b+num+1)-b-1;
	for(int i=1;i<=n;i++) {
		l[i]=lower_bound(b+1,b+num+1,l[i])-b,c[l[i]]++;
		r[i]=lower_bound(b+1,b+num+1,r[i])-b,c[r[i]]--;
	}
	for(int i=1,s=0;i<num;i++) {
		s+=c[i];
		if(R<=b[i]&&b[i+1]<=L)ans=min(ans,s);
	}cout<<(ans==n?-1:ans)<<"\n";
}
int main() {

	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tt;cin>>tt;
	while(tt--)solve();
	return 0;
}