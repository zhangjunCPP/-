#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,C;
int ans[N];
void solve(){
	cin>>n>>C;
	for(int i=1;i<=n;i++)ans[i]=0;
	if(C>n*n){puts("-1");return;}
	int k=ceil(C*1.0/n);
	ans[k]=n;
	int now=n*k;
	while(now>C){
		int tmp=k;
		while(ans[tmp]<ans[tmp-1]+2)tmp--;
		if(tmp==1){puts("-1");return;}
		ans[tmp]--,ans[tmp-1]++;
		now--;
	}
	int sum=0;
	for(int i=1;i<=k;i++)sum+=ans[i]*i*i;
	cout<<sum<<"\n"<<k<<"\n";
	for(int i=1;i<=k;i++)cout<<ans[i]<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
//注意到，如果我把相邻的，后面的减一，前面的加一，则第三个表达式减一 
//那么，我们可以这样：先指定一个位置有数，并且使第三个表达式尽可能接近C。
//然后，每次从后往前选第一个差大于1的两个数，进行更改