#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int a[N];
int cmpcnt;
void solve(vector<int> &tmp){
	int len=tmp.size();
	if(len<=1) return;
	int x=tmp[(len-1)/2];
	vector<int> tmp1,tmp2;
	for(int i=0;i<len;i++) {
		cmpcnt++;
		if(tmp[i]<x) tmp1.push_back(tmp[i]);
		if(tmp[i]>x) tmp2.push_back(tmp[i]);
	}
	solve(tmp1);
	solve(tmp2);
}
int dp[N];
int main(){
	// freopen("sort.in","r",stdin);
	// freopen("sort.out","w",stdout);
	dp[1]=0;
	dp[2]=2;
	dp[3]=3;
	dp[4]=6;
	for(int i=5;i<N;i++) {
		if(i&1) dp[i]=2*dp[i/2]+i;
		else dp[i]=dp[i/2-1]+dp[i/2]+i;
	}
	int last=0;
	for(int n=1;n<=100;n++){
		cout<<n<<" ";
	}
	return 0;
}