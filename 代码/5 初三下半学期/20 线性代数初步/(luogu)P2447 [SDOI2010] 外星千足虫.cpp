#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
bitset<N> a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		string s;
		cin>>s;
		for(int j=1;j<=n;j++)a[i][j]=s[j-1]-'0';
		int x;
		cin>>x;
		a[i][n+1]=x;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=m;j++)if(a[j][i]){swap(a[i],a[j]);ans=max(ans,j);break;}
		if(!a[i][i]){cout<<"Cannot Determine";return 0;}
		for(int j=1;j<=m;j++){
			if(j==i)continue;
			if(a[j][i])a[j]^=a[i];
		}
	}
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++){
		if(a[i][n+1])cout<<"?y7M#\n";
		else cout<<"Earth\n";
	}
}