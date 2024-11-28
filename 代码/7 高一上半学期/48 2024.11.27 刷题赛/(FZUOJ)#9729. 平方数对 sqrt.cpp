#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
bool vis[N];
int main(){
	int n,m;
	cin>>n>>m;
	if(n>m)swap(n,m);
	int ans=0;
	for(int i=2;i*i<=n;i++){
		int val=i*i;
		if(!vis[val])for(int j=val;j<=n;j+=val)vis[j]=true;
	}
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		int x=sqrt(n/i);
		int y=sqrt(m/i);
		ans+=x*y;
	}
	cout<<ans;
}