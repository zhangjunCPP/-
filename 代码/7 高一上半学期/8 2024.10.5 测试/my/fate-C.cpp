#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int ans[N];
int main(){
	freopen("fate10.in","r",stdin);
	freopen("fate10.ans","w",stdout);
	int n;
	cin>>n;
	if(n&1){cout<<":(";return 0;}
	for(int i=1;i<=n/2;i++)cout<<'(';
	for(int i=1;i<=n/2;i++)cout<<')';
	for(int i=1;i<=n/2;i++)cout<<'(';
	for(int i=1;i<=n/2;i++)cout<<')';

}