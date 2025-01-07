#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int G1[N],G2[N];
int v1[N],v2[N];
bool f1[N],f2[N];
int w1[N],w2[N];
int tmp1[N],tmp2[N];
int a[N],cnt1;
int b[N],cnt2;
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;
			cin>>ch;
			ch-='0';
			G1[i]|=ch<<(j-1);
			G2[j]|=ch<<(i-1);
		}
	}
	for(int i=1;i<=n;i++)cin>>v1[i];
	for(int i=1;i<=m;i++)cin>>v2[i];
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			if(i&(1<<j-1))w1[i]+=v1[j],tmp1[i]|=G1[j];
			f1[i]=(__builtin_popcount(i)<=__builtin_popcount(tmp1[i]));
		}
	}
	for(int i=0;i<(1<<n);i++)for(int j=1;j<=n;j++)if(i&(1<<j-1))f1[i]=min(f1[i],f1[i^(1<<j-1)]);
	for(int i=0;i<(1<<m);i++){
		for(int j=1;j<=m;j++){
			if(i&(1<<j-1))w2[i]+=v2[j],tmp2[i]|=G2[j];
			f2[i]=(__builtin_popcount(i)<=__builtin_popcount(tmp2[i]));
		}
	}
	for(int i=0;i<(1<<m);i++)for(int j=1;j<=m;j++)if(i&(1<<j-1))f2[i]=min(f2[i],f2[i^(1<<j-1)]);

	for(int i=0;i<(1<<n);i++)if(f1[i])a[++cnt1]=w1[i];
	for(int i=0;i<(1<<m);i++)if(f2[i])b[++cnt2]=w2[i];
	sort(a+1,a+1+cnt1);
	sort(b+1,b+1+cnt2);
	int t;
	cin>>t;
	int ans=0;
	int j=cnt2+1;
	for(int i=1;i<=cnt1;i++){
		while(j>1&&a[i]+b[j-1]>=t) j--;
		ans+=cnt2-j+1;
	}
	cout<<ans;
}