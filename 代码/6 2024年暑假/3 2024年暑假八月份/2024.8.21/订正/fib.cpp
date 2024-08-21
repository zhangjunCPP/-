#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
struct matrix {
	int mat[2][2]{};
	matrix operator*(const matrix&oth)const {
		matrix ans;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				for(int k=0;k<=1;k++)
					ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*oth.mat[k][j]%mod)%mod;
		return ans;
	}
};
matrix qpow(matrix x,int y) {
	matrix ans;
	ans.mat[0][0]=1,ans.mat[1][1]=1;
	while(y) {
		if(y&1)ans=ans*x;
		y>>=1;
		x=x*x;
	}
	return ans;
}
int nxt[N];
void get_nxt(string s) {
	//得到模式串s的nxt数组
	int len=s.length();
	int i=0,j=-1;
	nxt[i]=j;
	while(i<len) {
		if(j==-1||s[i]==s[j])nxt[++i]=++j;
		else j=nxt[j];
	}
}
int kmp(string s,string t) {
	//查询模式串s在文本串t中出现的次数
	int len1=s.size(),len2=t.size();
	int i=0,j=0;
	int ans=0;
	while(j<len2) {
		if(i==-1||s[i]==t[j])i++,j++;
		else i=nxt[i];
		if(i==len1)ans++;
	}
	return ans;
}
string fib[N];
void init() {
	fib[1]="0",fib[2]="1";
	for(int i=3;i<=27;i++)fib[i]=fib[i-1]+fib[i-2];
}
int n;
int calc(int x) {
	if(x<=2)return 1;
	matrix now;
	now.mat[0][0]=now.mat[1][0]=now.mat[0][1]=1;
	now.mat[1][1]=0;
	matrix ans=qpow(now,x-2);
	return (ans.mat[0][0]+ans.mat[1][0])%mod;
}
void solve() {
	string s;
	cin>>s;
	get_nxt(s);
	int len=s.size();
	int pos=-1;
	for(int i=1;i<=26;i++)if(fib[i].size()>=len){pos=i;break;}
	if(pos>=n) {
		cout<<kmp(s,fib[n])<<"\n";
		return;
	}
	int A=kmp(s,fib[pos]),B=kmp(s,fib[pos+1]),AB=kmp(s,fib[pos]+fib[pos+1])-A-B,BA=kmp(s,fib[pos+1]+fib[pos])-A-B,BB=kmp(s,fib[pos+1]+fib[pos+1])-B-B;
	A=A*calc(n-pos+1-2)%mod;
	B=B*calc(n-pos+1-1)%mod;
	AB=AB*(calc(n-pos+1-2)%mod+(((n-pos+1-2)&1)&&n-pos+1-2>0?-1:0)+mod)%mod;
	BA=BA*calc(n-pos+1-2)%mod;
	BB=BB*(calc(n-pos+1-3)%mod+(((n-pos+1-3)&1)&&n-pos+1-3>0?-1:0)+mod)%mod;
	cout<<(A+B+AB+BA+BB)%mod<<"\n";
}
signed main() {
	init();
	int T;
	cin>>n>>T;
	while(T--)solve();
}