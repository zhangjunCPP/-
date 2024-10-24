#include<bits/stdc++.h>
using namespace std;
int pw[35];
void init(){
	pw[0]=1;
	for(int i=1;i<31;i++)pw[i]=pw[i-1]*2;
}
void solve(){
	int n,k;
	cin>>n>>k;
	if(k==1){
		for(int i=30;i>=0;i--){
			if(n==pw[i]){
				cout<<i<<" ";
				for(int j=i-1;j>=0;j--)cout<<pw[j]<<" ";
				cout<<"\n";
				return;
			}
		}
		cout<<"-1\n";
		return;
	}
	vector<int> ans;
	bool flag=false;
	for(int i=30;i>=0;i--){
		if(n>=pw[i]){
			if(!flag){//第一次
				for(int j=0;j<i;j++)ans.push_back(pw[j]);
				n-=pw[i];
				flag=true;
			}
			else ans.push_back(pw[i]),n-=pw[i];
		}
	}
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<" ";
	for(int it:ans)cout<<it<<" ";
	cout<<"\n";
}
int main(){
	init();
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("sway.in","r",stdin);
	freopen("sway.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}

/*
倒着想？
最后要剩下1，那么最后取得一定是1个
而且任何时候都能取1
考虑倒数第二步，要求x|x+2，即x+2=kx
发现一个性质:如果b|a,那么gcd(a-b,a)=b，但我不会用

*/