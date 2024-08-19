#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n;
	cin>>n;
	int x=n/2,y=n-x;
	cout<<x*(x-1)/2+y*(y-1)/2;
}