#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll long long
	#define bl bool
	#define pf printf
	#define pc putchar
	#define fr(i,a,b) for(ll i=(a);i<=(b);i++)
	#define pfr(i,a,b) for(ll i=(a);i>=(b);i--)
	#define go(u) for(ll i=head[u];i;i=e[i].nxt)
	#define space pc(' ')
	#define enter pc('\n')
	#define il inline
	#define fir first
	#define sec second
	#define MP make_pair
	#define inf 8e18
	il ll read(){
		ll sum=0,fu=0;
		char ch=getchar();
		while(!isdigit(ch)){
			if(ch=='-') fu=1;
			ch=getchar();
		}
		while(isdigit(ch)){
			sum=sum*10+(ch-'0');
			ch=getchar();
		}
		return fu?(-sum):sum;
	}
	void write(ll x){
		if(x<0){
			pc('-');
			x=-x;
		}
		if(x>9) write(x/10);
		pc('0'+x%10);
	}
	il void writesp(ll x){
		write(x);
		space;
	}
	il void writeln(ll x){
		write(x);
		enter;
	}
}
using namespace my_std;
ll n,m,a[2][2][100010],cnt[2][2],ans=0;
int main(){
	n=read();
	m=read();
	fr(i,1,n){
		ll x=read(),y=read();
		a[0][x][++cnt[0][x]]=y;
	}
	fr(i,1,m){
		ll x=read(),y=read();
		a[1][x][++cnt[1][x]]=y;
	}
	fr(i,0,1) fr(j,0,1) sort(a[i][j]+1,a[i][j]+cnt[i][j]+1);
	fr(i,0,1){
		ll now=cnt[i^1][0];
		pfr(j,cnt[i][1],1){
			while(now>=1&&a[i^1][0][now]>=a[i][1][j]) now--;
			if(!now) break;
			ans+=a[i][1][j]+a[i^1][0][now];
			now--;
		}
	}
	write(ans);
}
