#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int mod=998244353,G=3,Gi=332748118;
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
}
int rev[N];
void calc_rev(int logn){
	rev[0]=0;
	for(int i=1;i<(1<<logn);i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(logn-1));
}
void NTT(int a[],int len,int opt){
	for(int i=0;i<len;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		int wn=qpow(opt?G:Gi,(mod-1)/(mid<<1));
		for(int j=0;j<len;j+=(mid<<1)){
			int w=1;
			for(int k=0;k<mid;k++,w=w*wn%mod){
				int x=a[j+k]%mod,y=w*a[j+k+mid]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+mid]=(x-y+mod)%mod;
			}
		}
	}
	if(!opt){
		int inv=qpow(len,mod-2)%mod;
		for(int i=0;i<len;i++)a[i]=a[i]*inv%mod;
	}
}
void mul(int a[],int b[],int n,int m){//多项式乘法
	int len=1,tmp=0;
	while(len<n+m)len<<=1,tmp++;
	calc_rev(tmp);
	NTT(a,len,1);
	NTT(b,len,1);
	for(int i=0;i<len;i++)a[i]=a[i]*b[i]%mod;
	NTT(a,len,0);
}
int Inv_tmp_f[N];
void Inv(int a[],int b[],int n){//多项式求逆
	if(n==1){
		b[0]=qpow(a[0],mod-2)%mod;
		return;
	}
	Inv(a,b,(n+1)>>1);
	int len=1,tmp=0;
	while(len<n*2)len<<=1,tmp++;
	calc_rev(tmp);
	for(int i=0;i<n;i++)Inv_tmp_f[i]=a[i];
	for(int i=n;i<len;i++)Inv_tmp_f[i]=0;
	NTT(Inv_tmp_f,len,1),NTT(b,len,1);
	for(int i=0;i<len;i++)b[i]=(2-Inv_tmp_f[i]*b[i]%mod+mod)%mod*b[i]%mod;
	NTT(b,len,0);
	for(int i=n;i<len;i++)b[i]=0;
	return;
}
int Sqrt_tmp_a[N],Sqrt_inv_b[N];
void Sqrt(int a[],int b[],int n){//多项式开根
	if(n==1){
		b[0]=1;
		return;
	}
	Sqrt(a,b,(n+1)>>1);
	int inv2=qpow(2,mod-2)%mod;
	for(int i=0;i<=n*2;i++)Sqrt_inv_b[i]=0;
	Inv(b,Sqrt_inv_b,n);
	int len=1,tmp=0;
	while(len<n*2)len<<=1,tmp++;
	calc_rev(tmp);
	for(int i=0;i<n;i++)Sqrt_tmp_a[i]=a[i];
	for(int i=n;i<len;i++)Sqrt_tmp_a[i]=0;
	NTT(b,len,1),NTT(Sqrt_tmp_a,len,1),NTT(Sqrt_inv_b,len,1);
	for(int i=0;i<len;i++)b[i]=(b[i]+Sqrt_tmp_a[i]*Sqrt_inv_b[i]%mod)%mod*inv2%mod;
	NTT(b,len,0);
	for(int i=n;i<len;i++)b[i]=0;
	return;
}
void Derivative(int a[],int b[],int n){//多项式求导
	for(int i=0;i<n-1;i++)b[i]=(i+1)*a[i+1]%mod;
}
void Integral(int a[],int b[],int n){//多项式不定积分
	for(int i=1;i<=n;i++)b[i]=a[i-1]*qpow(i,mod-2)%mod;
	b[0]=0;
}
int Ln_Der_a[N],Ln_inv_a[N];
void Ln(int a[],int b[],int n){//多项式求ln
	for(int i=0;i<n*2;i++)Ln_Der_a[i]=Ln_inv_a[i]=0;
	Derivative(a,Ln_Der_a,n);
	Inv(a,Ln_inv_a,n);
	mul(Ln_Der_a,Ln_inv_a,n-1,n);
	Integral(Ln_Der_a,b,n-1);
}
int Exp_Ln_b[N];
void Exp(int a[],int b[],int n){//多项式求exp
	if(n==1){
		b[0]=1;
		return;
	}
	Exp(a,b,(n+1)>>1);
	int len=1,tmp=0;
	while(len<n*2)len<<=1,tmp++;
	calc_rev(tmp);
	for(int i=0;i<len;i++)Exp_Ln_b[i]=0;
	Ln(b,Exp_Ln_b,len);
	Exp_Ln_b[0]=((a[0]+1)%mod-Exp_Ln_b[0]+mod)%mod;
	for(int i=1;i<len;i++)Exp_Ln_b[i]=(a[i]-Exp_Ln_b[i]+mod)%mod;
	mul(b,Exp_Ln_b,len,len);
	for(int i=n;i<len*2;i++)b[i]=0;
}
int Pow_Ln_a[N];
void Pow(int a[],int b[],int n,int k){
	Ln(a,Pow_Ln_a,n);
	for(int i=0;i<n;i++)Pow_Ln_a[i]=Pow_Ln_a[i]*k%mod;
	Exp(Pow_Ln_a,b,n);
}
int f[N],g[N];
int tmp[N];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		f[x]=1;
	}
	for(int i=0;i<=m;i++)f[i]=(-4*f[i]+mod);
	f[0]=(f[0]+1)%mod;
	Sqrt(f,tmp,m+1);
	tmp[0]=(tmp[0]+1)%mod;
	Inv(tmp,g,m+1);
	for(int i=0;i<=m;i++)g[i]=g[i]*2%mod;
	for(int i=1;i<=m;i++)cout<<g[i]<<"\n";
}