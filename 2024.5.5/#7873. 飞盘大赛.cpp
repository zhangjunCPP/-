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
#define goo(u) for(ll i=headd[u];i;i=e[i].nxt)
#define mod 998244853
ll n,m,a[110][110],d[110],inv2=(mod+1)/2,maxx=0,ans=0;
ll s,t,head[6060],headd[6060],cnt=1,dis[6060];
bl ck[6060];
struct node{
	ll nxt,to,w,c;
}e[60060];
void add(ll u,ll v,ll ww,ll cc){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].w=ww;
	e[cnt].c=cc;
	head[u]=cnt;
}
il bl spfa(){
	fr(i,s,t) headd[i]=head[i];
	fr(i,s,t) dis[i]=inf;
	dis[s]=1;
	queue<ll> q;
	q.push(s);
	ck[s]=1;
	while(!q.empty()){
		ll u=q.front();
		q.pop();
		ck[u]=0;
		go(u){
			ll v=e[i].to;
			if(e[i].w>0&&dis[v]>(dis[u]+e[i].c)){
				dis[v]=dis[u]+e[i].c;
				if(!ck[v]){
					ck[v]=1;
					q.push(v);
				}
			}
		}
	}
	return dis[t]!=inf;
}
ll dfs(ll u,ll sum){
	if(u==t) return sum;
	ck[u]=1;
	ll res=0;
	goo(u){
		ll v=e[i].to;
		if(!sum) break;
		if(!ck[v]&&e[i].w>0&&dis[v]==(dis[u]+e[i].c)){
			ll tmp=dfs(v,min(e[i].w,sum));
			maxx+=e[i].c*tmp;
			e[i].w-=tmp;
			e[i^1].w+=tmp;
			sum-=tmp;
			res+=tmp;
		}
		headd[u]=i;
	}
	ck[u]=0;
	return res;
}
int main(){
	n=read();
	m=read();
	fr(i,1,m){
		ll u=read(),v=read();
		a[u][v]=1;
		a[v][u]=2;
		d[u]++;
	}
	fr(i,1,n){
		fr(j,i+1,n){
			fr(k,j+1,n){
				ll tmp=1;
				if(!a[i][j]) tmp=tmp*inv2%mod;
				if(!a[j][k]) tmp=tmp*inv2%mod;
				if(!a[k][i]) tmp=tmp*inv2%mod;
				if(a[i][j]!=2&&a[j][k]!=2&&a[k][i]!=2) ans=(ans+tmp)%mod;
				if(a[i][j]!=1&&a[j][k]!=1&&a[k][i]!=1) ans=(ans+tmp)%mod;
			}
		}
	}
	s=0;
	t=n;
	fr(i,1,n){
		fr(j,i+1,n){
			if(a[i][j]) continue;
			t++;
			add(s,t,1,0);
			add(t,s,0,0);
			add(t,i,1,0);
			add(i,t,0,0);
			add(t,j,1,0);
			add(j,t,0,0);
		}
	}
	t++;
	fr(i,1,n){
		maxx+=d[i]*(d[i]-1)/2;
		fr(j,d[i],n-1){
			add(i,t,1,j);
			add(t,i,0,-j);
		}
	}
	while(spfa()) dfs(s,inf); 
	writesp(n*(n-1)*(n-2)/6-maxx);
	write(ans);
}
