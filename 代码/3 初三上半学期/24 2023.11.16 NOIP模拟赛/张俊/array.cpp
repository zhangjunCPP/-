#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum+=x;
	}
	if(n==1){cout<<sum;return 0;}
	if(n==2){cout<<(sum+1)/2;return 0;}

	return 0;
}

