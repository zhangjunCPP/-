#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int a1,b1,a2,b2;
		cin>>a1>>b1>>a2>>b2;
		int sum=(a2-a1+1)*(b2-b1+1);
		if(sum&1){puts("b");return 0;}
		else {puts("Iris");return 0;}
	}
}