#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	ll my_pow(ll a,ll b,ll mod){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res=(res*a)%mod;
			a=(a*a)%mod;
			b>>=1;
		}
		return res;
	}
	ll qpow(ll a,ll b){
		ll res=1;
		if(!b) return 1;
		while(b){
			if(b&1) res*=a;
			a*=a;
			b>>=1;
		}
		return res;
	}
	#define db double
	#define pf printf
	#define pc putchar
	#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
	#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define enter pc('\n')
	#define space pc(' ')
	#define fir first
	#define sec second
	#define MP make_pair
	#define il inline
	#define inf 8e18
	#define random(x) rand()*rand()%(x)
	#define inv(a,mod) my_pow((a),(mod-2),(mod))
	il ll read(){
		ll sum=0,f=1;
		char ch=0;
		while(!isdigit(ch)){
			if(ch=='-') f=-1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch^48);
			ch=getchar();
		}
		return sum*f;
	}
	il void write(ll x){
		if(x<0){
			x=-x;
			pc('-');
		}
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
	il void writesp(ll x){
		write(x);
		space;
	}
}
using namespace my_std;
#define mod 1000000007
ll n,a[33],b[33],sum=0,jc[6060],jcinv[6060],ans=0;
ll V=0,A[33][33],val[220],B[3030],f[3030],g[3030],h[3030];
il ll gauss(){
	ll res=1;
	fr(i,1,n){
		ll tmp=i;
		fr(j,i,n) if(A[j][i]) tmp=j;
		if(i!=tmp){
			swap(A[i],A[tmp]);
			res=(mod-res)%mod;
		}
		if(!A[i][i]) return 0;
		res=res*A[i][i]%mod;
		tmp=inv(A[i][i],mod);
		fr(j,i,n) A[i][j]=A[i][j]*tmp%mod;
		fr(j,i+1,n){
			tmp=A[j][i];
			fr(k,i,n) A[j][k]=(A[j][k]-tmp*A[i][k]%mod+mod)%mod;
		}
	}
	return res;
}
il void lagrange(){
	g[0]=1;
	fr(i,0,sum/2){
		pfr(j,i+1,0){
			g[j]=g[j]*(mod-i)%mod;
			if(j) g[j]=(g[j]+g[j-1])%mod;
		}
	}
	fr(i,0,sum/2){
		ll tmp=B[i]*jcinv[i]%mod*jcinv[sum/2-i]%mod;
		if((sum/2-i)&1) tmp=(mod-tmp)%mod;
		pfr(j,sum/2,0) h[j]=(g[j+1]+i*h[j+1]%mod)%mod;
		fr(j,0,sum/2) f[j]=(f[j]+tmp*h[j]%mod)%mod;
	}
}
int main(){
	n=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n) b[i]=read();
	fr(i,1,n) sum+=b[i]-a[i];
	fr(i,1,n) fr(j,1,n) if(a[i]<a[j]&&b[i]>b[j]) sum=-inf;
	if(sum<0||(sum&1)){
		write(0);
		return 0;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	jc[0]=1;
	fr(i,1,sum) jc[i]=jc[i-1]*i%mod;
	jcinv[sum]=inv(jc[sum],mod);
	pfr(i,sum-1,0) jcinv[i]=jcinv[i+1]*(i+1)%mod;
	fr(i,1,n) fr(j,1,n) V=max(V,b[j]-a[i]);
	fr(i,0,sum/2){
		fr(j,0,V){
			ll mul=1;
			val[j]=0;
			fr(k,0,j/2){
				if(k&1) val[j]=(val[j]-jcinv[k]*jcinv[j-2*k]%mod*mul%mod+mod)%mod;
				else val[j]=(val[j]+jcinv[k]*jcinv[j-2*k]%mod*mul%mod)%mod;
				mul=mul*i%mod;
			}
		}
		fr(j,1,n){
			fr(k,1,n){
				if(a[j]>b[k]) A[j][k]=0;
				else A[j][k]=val[b[k]-a[j]];
			}
		}
		B[i]=gauss();
	}
	lagrange();
	fr(i,0,sum/2) ans=(ans+f[i]*jcinv[sum/2-i]%mod*jc[sum-2*i]%mod)%mod;
	write(ans*jc[sum/2]%mod*my_pow((mod+1)/2,sum/2,mod)%mod);
}
