#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int ans[N];
int main(){
	freopen("fate6.in","r",stdin);
	freopen("fate6.ans","w",stdout);
	int n;
	cin>>n;
	if(n&1){cout<<":(";return 0;}
	for(int i=1;i<=n;i+=2){
		ans[i]=ans[i+1]=1;
		ans[n*2-i+1]=ans[n*2-i]=2;
	}
	for(int i=1;i<=2*n;i++)cout<<(ans[i]==1?'(':')');

}