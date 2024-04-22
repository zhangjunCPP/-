#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
const int N=105,M=1e5+5;
struct matrix{
	int x[N][N];
	matrix(){memset(x,0,sizeof(x));}
	matrix operator*(const matrix&b)const{
		matrix ans;
        for(int i=0;i<N;i++)for(int j=0;j<N;j++)for(int k=0;k<N;k++)ans.x[i][j]=(ans.x[i][j]+x[i][k]*b.x[k][j])%mod;
        return ans;
	} 
}ans,x;
matrix qpow(matrix ans,matrix x,int y){
	while(y){ 
		if(y&1)ans=x*ans;
		x=x*x;
		y>>=1;
	}
	return ans;
}
int qpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        y>>=1;
        x=x*x%mod;
    }
    return ans%mod;
}
int p[N];
signed main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<k;i++){
        ans.x[i][i]=1;
        int a,b;
        cin>>a>>b;
        p[i]=a*qpow(b,mod-2)%mod;
        x.x[i][i+1]=1-p[i]+mod;
        x.x[i][0]=x.x[i][k+1]=p[i];
    }
    p[k]=x.x[k][0]=x.x[k][k+1]=x.x[k+1][k+1]=1;
    ans.x[k+1][k+1]=1;
    ans=qpow(ans,x,n);
    cout<<ans.x[0][k+1];
}