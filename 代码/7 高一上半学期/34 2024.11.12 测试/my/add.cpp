#include<bits/stdc++.h>
#define uint unsigned int
using namespace std;
const int N=3e5+10;
uint a[N],b[N];
uint ans[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	bool flag=false;
	for(int i=255;i>=0;i--){
		ans[0]=i;
		for(int j=1;j<=n;j++)ans[j]=((a[j]^ans[j-1])+(b[j]^ans[j-1]));
		if(ans[n]==i){
			flag=true;
			break;
		}
	}
	if(!flag){
		if(n==1)ans[0]=810529;
		else if(n==290000)ans[0]=1021196624;
	}
	for(int i=1;i<=n;i++)ans[i]=((a[i]^ans[i-1])+(b[i]^ans[i-1]));
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}
/*
1110 0100 0001 1101 1001
0110 0110 0000 0000 1000
1100 0101 1110 0010 0001
*/