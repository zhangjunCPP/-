#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,INF=1e9;
int a[N];
int p[N];
int sum[N];
int tmp[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],sum[a[i]]=1;
	for(int i=1;i<=10;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=10;i++)p[i]=i;
	int ans=INF;
	do{
		int Max=0;
		for(int i=1;i<=n;i++){
			int l=1,r=10;
			int val=0;
			for(int j=1;j<=10;j++){
				if(sum[r]-sum[l-1]==1)break;
				val+=abs(a[i]-p[j]);
				if(a[i]>=p[j])l=max(l,p[j]);
				else r=min(r,p[j]-1);
			}
			Max=max(Max,val);
		}
		ans=min(ans,Max);
	}while(next_permutation(p+1,p+10+1));
	cout<<ans;
}