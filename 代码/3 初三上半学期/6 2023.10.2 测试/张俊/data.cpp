#include<bits/stdc++.h>
#define int long long
using namespace std;
int random(int l,int r){
	return (rand()*rand())%(r-l+1)+l;
}
signed main(){
	freopen("b.in","w",stdout);
	srand(time(0));
	int n=random(1,2000);
	cout<<n<<"\n";
	while(n){
		int val=random(1,1000000000);
		int sum=random(1,(n+1)/2);
		for(int i=1;i<=sum;i++) cout<<val<<" ";
		n-=sum;
	}
}
