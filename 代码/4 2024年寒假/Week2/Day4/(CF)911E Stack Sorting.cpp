#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N];
int s[N],cnt;
int need=1;
signed main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i];
		s[++cnt]=a[i];
		while(s[cnt]==need) need++,cnt--;
	}
	bool ans=true;
	for(int i=cnt;i>=2;i--) if(s[i]>s[i-1]) ans=false;
	if(!ans) {puts("-1");return 0;}
	for(int i=1;i<=k;i++) cout<<a[i]<<" ";
	s[cnt+1]=need-1;
	for(int i=cnt;i>=1;i--)for(int j=s[i]-1;j>s[i+1];j--)cout<<j<<" ";
	for(int i=n;i>s[1];i--)cout<<i<<" ";
	return 0;
}