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
int ans[N];
int main(){
	string a,b;
	cin>>a>>b;
	int n=a.size()-1,m=b.size()-1;
	for(int i=0;i<=n;i++)f[i]=double(a[n-i]-'0');
	for(int i=0;i<=m;i++)g[i]=double(b[m-i]-'0');
	int tmp=0;
	while(len<=n+m)len<<=1,tmp++;
	for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(tmp-1));
	FFT(f,1);
	FFT(g,1);
	for(int i=0;i<len;i++)f[i]*=g[i];
	FFT(f,-1);
	for(int i=0;i<len;i++){
		ans[i]+=(int)(f[i].real()/len+0.5);
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	while(!ans[len]&&len>=0)len--;
	if(len==-1)cout<<"0";
	else for(int i=len;i>=0;i--)cout<<ans[i];
}