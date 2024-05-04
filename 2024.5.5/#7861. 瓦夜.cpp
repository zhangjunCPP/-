#include<bits/stdc++.h>
using namespace std;
namespace my_std{
	#define ll int
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
	il long long read(){
		long long sum=0,fu=0;
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
ll tid,n,m,head[25000025],nxt[800080],val[800080],ans[400040];
long long to[800080];
ll ch[25000025][2],rt=1,tot=1;
struct trie{
	ll tree[25000025],ch[25000025][2],rt=1,tot=1;
	il void ins(long long w,ll v){
		ll x=rt;
		while(w){
			bl o=w&1;
			if(!ch[x][o]) ch[x][o]=++tot;
			x=ch[x][o];
			w>>=1;
		}
		tree[x]+=v;
	}
	il ll query(long long w){
		ll x=rt,res=0;
		while(w&&x){
			res+=tree[ch[x][1]];
			x=ch[x][w&1];
			w>>=1;
		}
		return res;
	}
}T;
void dfs(ll x){
	for(ll i=head[x];i;i=nxt[i]) if(i>n) ans[i-n]=T.query(to[i]);
	for(ll i=head[ch[x][1]];i;i=nxt[i]) if(i<=n) T.ins(to[i],val[i]);
	fr(i,0,1) if(ch[x][i]) dfs(ch[x][i]);
	for(ll i=head[ch[x][1]];i;i=nxt[i]) if(i<=n) T.ins(to[i],-val[i]);
}
int main(){
	tid=read();
	n=read();
	m=read();
	fr(i,1,n){
		long long x=read(),y=read(),w=read(),u=rt;
		while(x){
			bl o=x&1;
			if(!ch[u][o]) ch[u][o]=++tot;
			u=ch[u][o];
			x>>=1;
		}
		nxt[i]=head[u];
		to[i]=y;
		val[i]=w;
		head[u]=i;
	}
	fr(i,1,m){
		long long x=read(),y=read(),u=rt;
		while(x){
			bl o=x&1;
			if(!ch[u][o]){
				ch[u][o]=++tot;
				u=ch[u][o];
				break;
			}
			u=ch[u][o];
			x>>=1;
		}
		nxt[n+i]=head[u];
		to[n+i]=y;
		head[u]=n+i;
	}
	dfs(1);
	fr(i,1,m) writeln(ans[i]);
}
