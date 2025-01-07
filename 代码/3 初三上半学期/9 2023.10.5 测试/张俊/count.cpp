#include<bits/stdc++.h>
using namespace std;
const int N=1e8+10;
int sum[N];
int ans[100000];
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		int tmp=0;
		for(int i=1;i<=n*n;i++)sum[i]=0;
		for(int a1=1;a1<=n;a1++)for(int d1=1;d1<=n;d1++) sum[a1*d1]++;
		for(int i=1;i<=n*n;i++)tmp+=sum[i]*sum[i];
		cout<<tmp<<"\n";
		ans[n]=tmp;
	}
	return 0;
}