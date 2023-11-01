#include <bits/stdc++.h>
using namespace std;
long long a[50005],L,N,M;
int check(int dis) {
	int cnt=0,start=0;
	for(int i=1; i<=N+1; i++) {	
		if(a[i]-start<dis) cnt++;
		else start=a[i];
	}
	if(cnt>M) return 0;
	else return 1;
}
int main() {
	cin>>L>>N>>M;
	for(int i=1; i<=N; i++)cin>>a[i];
	a[N+1]=L;
	long long l=0,r=L,ans;
	while(l<=r) {
		long long mid=(l+r)/2;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}