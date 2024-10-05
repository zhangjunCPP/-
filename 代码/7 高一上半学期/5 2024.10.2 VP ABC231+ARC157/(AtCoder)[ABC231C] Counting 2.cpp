#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	while(q--){
		int x;
		cin>>x;
		cout<<n-(lower_bound(a+1,a+n+1,x)-a-1)<<"\n";
	}
}