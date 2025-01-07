#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=10000;
int pw[N];

int a[N];
bool vis[N];
int nex[N];
void print(int x){
	if(x<10) putchar('0');
	if(x<100) putchar('0');
	if(x<1000) putchar('0');
	cout<<x<<"\n";
}
signed main(){
	int n,t;
	cin>>n>>t;
	pw[0]=1;
	for(int i=1;i<N;i++) pw[i]=(pw[i-1]*n)%mod;
	while(t--){
		int m;
		cin>>m;
		for(int i=1;i<=m;i++) cin>>a[i];
		for(int i=0;i<=m+10;i++) vis[i]=nex[i]=0;

		for(int i=2,j=0;i<=m;i++){
			while(j&&a[j+1]!=a[i]) j=nex[j];
			if(a[j+1]==a[i]) nex[i]=j+1,j++;
		}

		for(int i=m;i;i=nex[i]) vis[i]=true;
		int ans=0;
		for(int i=1;i<=m;i++){
			if(vis[i])ans=(ans+pw[i])%mod;
		}
		print(ans);
	}
}