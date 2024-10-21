#include<bits/stdc++.h>
#define ll long long
using namespace std;const int N=1e6+5,M=N*4,K=2e5+5;
bool Be;
int n,m,q,mxl,w[N],p[N],bl[N],a[K],b[K];string S[K],C[K];vector<int>s[K];vector<ll>d[K];
int cv(char c){return c-'a';}
int cal(int v,int w){return w<a[v]+mxl?w-a[v]:(w-a[v]-mxl)%b[v]+mxl;}
ll sol(int v,int w){if(w<a[v]+mxl)return w<a[v]?0:d[v][w-a[v]];
	return d[v][(w-a[v]-mxl)%b[v]+mxl]+(w-a[v]-mxl)/b[v]*(d[v][mxl-1+b[v]]-d[v][mxl-1]);
}
struct ACM{int tot,ch[K][26],fa[K],cnt[K];vector<int>v;queue<int,list<int>>q;
	void init(){
		for(auto k:v){int len=S[k].size(),u=0;
			for(int op,i=0;i<len;i++)!ch[u][op=cv(S[k][i])]&&(ch[u][op]=++tot),u=ch[u][op];cnt[u]++;
		}q.push(0);
		while(!q.empty()){int u=q.front();q.pop(),cnt[u]+=cnt[fa[u]];
			for(int i=0;i<26;i++)if(!ch[u][i])ch[u][i]=ch[fa[u]][i];
				else fa[ch[u][i]]=u?ch[fa[u]][i]:0,q.push(ch[u][i]);
		}
	}
}acm;
struct SGT{int l[M],r[M],g[M];ll f[M];
#define ls (k<<1)
#define rs (k<<1|1)
	void pu(int k){f[k]=f[ls]+f[rs];}void Pd(int k,int v){g[k]=v,f[k]=sol(v,r[k])-sol(v,l[k]-1);}
	void pd(int k){if(~g[k])Pd(ls,g[k]),Pd(rs,g[k]),g[k]=-1;}
	void build(int L=1,int R=n,int k=1){l[k]=L,r[k]=R;if(L==R)return;
		int mid=L+R>>1;build(L,mid,ls),build(mid+1,R,rs);
	}
	void add(int L,int R,int v,int k=1){if(R<l[k]||r[k]<L)return;
		if(L<=l[k]&&r[k]<=R)return Pd(k,v);pd(k),add(L,R,v,ls),add(L,R,v,rs),pu(k);
	}
	ll ask(int L,int R,int k=1){if(R<l[k]||r[k]<L)return 0;
		if(L<=l[k]&&r[k]<=R)return f[k];return pd(k),ask(L,R,ls)+ask(L,R,rs);
	}
	void change(int L,int R,int k=1){if(R<l[k]||r[k]<L)return;
		if(l[k]==r[k])return bl[l[k]]=g[k],void();pd(k),change(L,R,ls),change(L,R,rs);
	}
#undef ls
#undef rs
}sgt;
ll ask(int l,int r){ll res=sgt.ask(l+mxl,r);int u=0;sgt.change(l,min(r,l+mxl-1));
	for(int u=0,j=1,i=l;i<=r&&j<=mxl;i++,j++)u=acm.ch[u][cv(C[bl[i]][cal(bl[i],i)])],res+=acm.cnt[u];
	return res;
}
void add(int l,int r,int v){string now="";while(now.size()<mxl)now+=C[v];
	C[v]+=now,sgt.change(l-1,l-1);int u=l==1?0:s[bl[l-1]][cal(bl[l-1],l-1)];ll sum=0;int len=C[v].size();
	for(int i=0;i<len;i++)u=acm.ch[u][cv(C[v][i])],sum+=acm.cnt[u],s[v].push_back(u),d[v].push_back(sum);
	sgt.add(l,r,v),u=s[v][cal(v,r)],sgt.change(r+1,min(n,r+mxl-1)),sum=0;
	for(int j=1,i=r+1;i<=n&&j<=mxl;i++,j++){C[v+q].push_back(C[bl[i]][cal(bl[i],i)]);
		u=acm.ch[u][cv(C[v+q].back())],sum+=acm.cnt[u],s[v+q].push_back(u),d[v+q].push_back(sum);
	}a[v+q]=r+1,b[v+q]=n,sgt.add(r+1,min(n,r+mxl-1),v+q);
}
bool Ed;
int main(){

	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<(&Be-&Ed)/1024.0/1024<<"\n";
	cin>>n>>m>>q>>C[0],a[0]=1,b[0]=n;
	for(int i=1;i<=m;i++)cin>>S[i],mxl=max(mxl,(int)S[i].size()),acm.v.push_back(i);acm.init();ll sum=0;
	for(int u=0,i=1;i<=n;i++)u=acm.ch[u][cv(C[0][i-1])],sum+=acm.cnt[u],s[0].push_back(u),d[0].push_back(sum);
	sgt.build(),sgt.Pd(1,0);
	for(int op,x,y,i=1;i<=q;i++){cin>>op>>x>>y;
		if(op==1)cout<<ask(x,y)<<"\n";else cin>>C[i],a[i]=x,b[i]=C[i].size(),add(x,y,i);
	}
}
