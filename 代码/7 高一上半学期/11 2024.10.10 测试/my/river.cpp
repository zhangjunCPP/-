#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int h[N];
void solve(){
	int n,l,r;
	cin>>n>>l>>r;
	int t=(n-l-1)/(r-l),sum=0;
	for(int i=1;i<=n;i++){
		cin>>h[i];
		sum+=min(t,(h[i]-1)/2);
	}
	cout<<(sum>=l*t?"Yes":"No")<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}
/*
贪心？
每次选择体力值最大的l个人的和最小的r-l个人
然后再把体力值前l大的送回来？
*/