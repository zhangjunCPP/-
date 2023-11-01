#include <bits/stdc++.h>
using namespace std;
long long  a[50005],L,N,M;
int check(int dis) {
	int cnt=0,start=0;                  //cnt总移动石头数 start每次移动起始位置(第一次在起点0)
	for(int i=1; i<=N+1; i++) {			 //N+1因为包含终点
		if(a[i]-start<dis) cnt++;	    //距离尽可能长,小于要挪走
		else start=a[i];			    //大于即符合题意,更新起跳点
	}
	if(cnt>M) return 0;
	else return 1;
}
int main() {
	cin>>L>>N>>M;
	for(int i=1; i<=N; i++) {
		cin>>a[i];
	}
	a[N+1]=L;							//终点的石头
	long long l=0,r=L,ans;
	while(l<=r) {
		long long mid=(l+r)/2;
		if(check(mid)) {
			ans=mid;
			l=mid+1;
		} else r=mid-1;
	}
	cout<<ans;
	return 0;
}