#include<bits/stdc++.h>
using namespace std;
const int mod=2009;
int n,MAX;
int a[105][105];
struct matrix{
	int x[105][105];
	int n,m;
	matrix(){memset(x,0,sizeof(x));}
	matrix operator*(const matrix&b) const{
		matrix ans;
		ans.n=n,ans.m=b.m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=b.m;j++)
				for(int k=1;k<=m;k++)
					ans.x[i][j]=(ans.x[i][j]+x[i][k]*b.x[k][j]%mod)%mod;
		return ans;
	}
}now;
matrix qpow(matrix x,int y){
	matrix ans;
	ans.m=ans.n=n;
	for(int i=1;i<=n;i++) ans.x[i][i]=1;
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
int f(int i,int j){return (i-1)*MAX+j;}
int main(){
	int t;
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%1d",&a[i][j]);
			MAX=max(MAX,a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<MAX;j++)now.x[f(i,j)][f(i,j+1)]=1;
		for(int j=1;j<=n;j++){
			if(a[i][j])
				now.x[f(i,a[i][j])][f(j,1)]=1;

		}
	}
	n*=MAX;
	now.m=now.n=n;
	now=qpow(now,t);
	cout<<now.x[1][n-MAX+1];
}