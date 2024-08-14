#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
void solve() {
	int n;
	cin>>n;
	int sum=4*n*n;
	int Max=5*n,Min=3*n;
	cout<<Max<<" "<<Min<<" ";
	if(n&1)cout<<4*n<<" ";
	for(int i=1;i<=(n-2)/2;i++)cout<<4*n-i<<" "<<4*n+i<<" ";
	cout<<"\n";
}
int main() {
	int T;
	cin>>T;
	while(T--)solve();
}