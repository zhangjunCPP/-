#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+10;
const int mod=998244353,G=3,Gi=332748118;
int f[N],g[N];
int len=1;
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
void NTT(int a[],int opt){
	for(int i=0;i<len;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		int wn=qpow(opt?G:Gi,(mod-1)/(mid<<1));
		for(int j=0;j<len;j+=(mid<<1)){
			int w=1;
			for(int k=0;k<mid;k++,w=w*wn%mod){
				int x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=(x+y)%mod;
				a[j+k+mid]=(x-y+mod)%mod;
			}
		}
	}
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;i++)cin>>f[i];
	for(int i=0;i<=m;i++)cin>>g[i];
	int tmp=0;
	while(len<=n+m)len<<=1,tmp++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(tmp-1));
	NTT(f,1);
	NTT(g,1);
	for(int i=0;i<len;i++)f[i]=f[i]*g[i]%mod;
	NTT(f,0);
	int inv=qpow(len,mod-2);
	for(int i=0;i<=n+m;i++)cout<<(f[i]*inv%mod+mod)%mod<<" ";
}