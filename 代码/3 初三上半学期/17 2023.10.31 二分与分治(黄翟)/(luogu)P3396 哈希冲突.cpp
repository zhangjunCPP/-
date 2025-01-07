#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int n,m;
int a[N];
int mo[N][500];
int main(){
	cin>>n>>m;
	int k=pow(n,0.33);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)mo[j][i%j]+=a[i];
	while(m--){
		string cmd;
		int x,y;
		cin>>cmd>>x>>y;
		if(cmd=="A"){
			int ans=0;
			if(x>=k) for(int i=y;i<=n;i+=x)ans+=a[i];
			else ans=mo[x][y];
			cout<<ans<<'\n';
		}
		else{
			for(int i=1;i<=k;i++)mo[i][x%i]+=y-a[x];
			a[x]=y;
		}
	}
}