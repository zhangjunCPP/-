#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int mod=998244353;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
int fac[N],inv[N];
void init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int n,int m){if(m>n||m<0||n<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	init();
	string s;
	cin>>s;
	int n=s.size();
	int cnt_left=0,cnt_right=0,cnt_unknow=0;
	for(int i=0;i<n;i++){
		if(s[i]=='(')cnt_left++;
		if(s[i]==')')cnt_right++;
		if(s[i]=='?')cnt_unknow++;
	}
	int ans=0;
	int cnt1=0,cnt2=0,cnt3=0;
	for(int i=0;i<n;i++){
		if(s[i]=='(')cnt1++;
		if(s[i]==')')cnt2++;
		if(s[i]=='?')cnt3++;
		int a=cnt1,b=cnt_right-cnt2,x=cnt3,y=cnt_unknow-cnt3;
		ans=(ans+b*C(x+y,y+b-a)%mod+y*C(x+y-1,y+b-a)%mod)%mod;
	}
	cout<<ans;
}