#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=1e7+5,inf=(1LL<<31)-1;
bool vis[N];
int pre[N],p[N],cnt,dist[6],in[6];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int dis(int a,int b){
	return 1LL*a*b/gcd(a,b);
}
void prep(){
	rep(i,2,N-5){
		if(!vis[i])p[++cnt]=i,pre[i]=2;
		for(int j=1;j<=cnt&&p[j]*i<=N-5;j++){
			vis[p[j]*i]=1,pre[i*p[j]]=p[j];
			if(i%p[j]==0)break;
		}
	}
}
vector<int>d;
void bfs(){
	queue<int>q;
	rep(i,1,5)in[i]=0,dist[i]=inf;
	in[1]=1,dist[1]=0,q.push(1);
	while(!q.empty()){
		int x=q.front();q.pop();
		in[x]=0;
		rep(i,1,5){
			int w=dis(d[x],d[i]);
			if(dist[i]>dist[x]+w){
				dist[i]=dist[x]+w;
				if(!in[i])q.push(i),in[i]=1;
			}
		}
	}
}
signed main(){
	prep();
	int T=read();
	while(T--){
		int a=read(),b=read();
		if(a==b)puts("0");
		else if(b%a==0)cout <<b<<'\n';
		else if(gcd(a,b)!=1)cout <<a+b<<'\n';
		else d={0,a,pre[a],2,pre[b],b},bfs(),cout <<dist[5]<<'\n';
	}
	return 0;
}