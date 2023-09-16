#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
double dp1[N],dp2[N],dp3[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		double p;
		cin>>p;
		dp1[i]=(dp1[i-1]+1)*p;
		dp2[i]=(dp2[i-1]+2*dp1[i-1]+1)*p;
		dp3[i]=dp3[i-1]+(3*dp2[i-1]+3*dp1[i-1]+1)*p;
	}
	printf("%.1lf",dp3[n]);
	return 0;
}
