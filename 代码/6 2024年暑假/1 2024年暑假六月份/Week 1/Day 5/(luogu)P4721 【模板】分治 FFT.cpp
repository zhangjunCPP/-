#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=998244353,G=3,Gi=332748118;
int f[N],g[N];
int rev[N];
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans%mod;
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
}
int a[N],b[N];
void calc_rev(int logn){
	rev[0]=0;
	for(int i=1;i<(1<<logn);i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(logn-1));
}
void solve(int l,int r,int logn){
	if(logn==0)return;
	int mid=(l+r)>>1;
	solve(l,mid,logn-1);
	calc_rev(logn);
	memset(a+(r-l)/2,0,sizeof 1ll*(r-l)/2);
	memcpy(a,f+l,sizeof 1ll*(r-l)/2);
	memcpy(b,g,sizeof 1ll*(r-l));
	NTT(a,1ll<<logn,1);NTT(b,1ll<<logn,1);
	for(int i=0;i<r-l;i++)a[i]=a[i]*b[i]%mod;
	NTT(a,1ll<<logn,0);
	int inv=qpow(r-l,mod-2)%mod;
	for(int i=0;i<r-l;i++)a[i]=a[i]*inv%mod;
	for(int i=(r-l)/2;i<r-l;i++)f[l+i]=(f[l+i]+a[i])%mod;
	solve(mid,r,logn-1);
}
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<n;i++)cin>>g[i];
	f[0]=1;
	int len=1,tmp=0;
	while(len<n)len<<=1,tmp++;
	solve(0,1ll<<tmp,tmp);
	for(int i=0;i<n;i++)cout<<f[i]<<" ";
}