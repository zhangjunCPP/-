#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int sum[N];
int main(){
	int n,k;
	string s;
	cin>>n>>k>>s;
	int cnt_x=0,cnt_y=0;
	for(int i=0;i<n;i++)if(s[i]=='X')cnt_x++;else cnt_y++;
	if(k>cnt_x){//一个简便的实现：由于所有的X都要反转，且不能重复，因此我们可以直接把原序列反转，再把一些反转后的X重新变回Y（这些是不该被翻的，剩下的X是该翻的）。
		for(int i=0;i<n;i++)s[i]=(s[i]=='X')?'Y':'X';
		k=n-k;
		swap(cnt_x,cnt_y);
	}
	if(cnt_x==n){
		cout<<max(0,k-1);
		return 0;
	}
	int last=-1;
	for(int i=0;i<n;i++){
		if(s[i]=='Y'){
			if(last!=-1)sum[i-last-1]++;
			last=i;
		}
	}
	int ans=0;
	for(int i=1;i<=n&&k;i++){
		while(sum[i]&&k){
			if(i<=k)ans+=i+1,k-=i,sum[i]--;
			else ans+=k,k=0;
		}
	}
	ans+=k;
	ans+=sum[0];
	cout<<ans;
}