#include<bits/stdc++.h>
#define int long long
using namespace std; 
const int mod=1e9+7;
struct matrix{
	int a[3][3];
	matrix (){memset(a,0,sizeof a);}
	matrix operator*(const matrix &b) const{
		matrix ans;
		for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++)ans.a[i][j]=(ans.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
		return ans;
	}
}x,y,ans;
void init() {
	ans.a[0][0]=1;
	x.a[0][0]=1,x.a[0][1]=0,x.a[0][2]=1;
	x.a[1][0]=2,x.a[1][1]=1,x.a[1][2]=2;
	x.a[2][0]=1,x.a[2][1]=1,x.a[2][2]=2;
	y.a[0][0]=1,y.a[0][1]=0,y.a[0][2]=0;
	y.a[1][0]=2,y.a[1][1]=1,y.a[1][2]=0;
	y.a[2][0]=1,y.a[2][1]=1,y.a[2][2]=1;
}
void qpow(matrix X,int Y) {
	while(Y){
		if(Y&1) ans=X*ans;
		X=X*X;
		Y>>=1;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	init();
	int n,m;
	cin>>n>>m;
	int pre=-1;
	for(int i=1;i<=m;i++) {
		int tmp;
		cin>>tmp;
		int last=tmp-pre-1;
		qpow(x,last);
		ans=y*ans;
		pre=tmp;
	}
	int last=n-pre-1;
	qpow(x,last);
	cout<<ans.a[2][0];
	return 0;
}
