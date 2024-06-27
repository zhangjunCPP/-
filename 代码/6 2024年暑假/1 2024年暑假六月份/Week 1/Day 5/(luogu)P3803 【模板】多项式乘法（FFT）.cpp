#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
const double pi=acos(-1.0);
complex<double> f[N],g[N];
int len=1;
int rev[N];
void FFT(complex<double> a[],int opt){
	for(int i=0;i<len;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<len;mid<<=1){
		complex<double> wn(cos((2*pi)/(mid<<1)),opt*sin((2*pi)/(mid<<1)));
		for(int j=0;j<len;j+=(mid<<1)){
			complex<double> w(1,0);
			for(int k=0;k<mid;k++,w*=wn){
				complex<double> x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=x+y;
				a[j+k+mid]=x-y;
			}
		}
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n;i++)cin>>f[i];
	for(int i=0;i<=m;i++)cin>>g[i];
	int tmp=0;
	while(len<=n+m)len<<=1,tmp++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(tmp-1));
	FFT(f,1);
	FFT(g,1);
	for(int i=0;i<len;i++)f[i]*=g[i];
	FFT(f,-1);
	for(int i=0;i<=n+m;i++)cout<<int(f[i].real()/len+0.5)<<" ";
}