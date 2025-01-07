#include<bits/stdc++.h>
using namespace std;
#define LL long long
template<typename tp>inline void chemx(tp &a,tp b){a<b?a=b:0;}
template<typename tp>inline void chemn(tp &a,tp b){a>b?a=b:0;}
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
const int N=200005;
int n,inc[N],id[N],cirlen,vis[N],fa[N],findcircle,d[N],odis[N],mxd[N],a[N],ans[N];
vector<int>e[N],son[N];
void tarjan(int u){
	vis[u]=1;
	if(findcircle)return;
	for(int v:e[u])if(v!=fa[u]){
		if(findcircle)return;
		if(!vis[v]){
			vis[v]=1;
			fa[v]=u;
			tarjan(v);
		}else{
			int x=u;
			do{
				inc[x]=1;
				id[++cirlen]=x;
				x=fa[x];
			}while(x!=v);
			inc[v]=1;
			id[++cirlen]=v;
			findcircle=1;
		}
	}
}
void dfs(int u,int fa){
	for(int v:e[u])if(!inc[v]&&v!=fa){
		dfs(v,u);
		son[u].push_back(mxd[v]+1);
		mxd[u]=max(mxd[u],mxd[v]+1);
	}
}
void calc_odis(){
	for(int i=cirlen+1;i<=cirlen*2;i++)a[i]=a[i-cirlen],id[i]=id[i-cirlen];
	int del=(cirlen+1)/2;
	multiset<int>s1,s2;
	for(int i=1;i<=del;i++)s2.insert(a[i]-i);
	for(int i=1;i<=cirlen*2;i++){
		int j=i+del;
		s2.erase(s2.find(a[i]-i));
		if(j<=cirlen*2)s2.insert(a[j]-j);
		if(s1.size())
		odis[id[i]]=max(odis[id[i]],(*s1.rbegin())+cirlen-i);
		if(s2.size())
		odis[id[i]]=max(odis[id[i]],(*s2.rbegin())+cirlen+i);
		j=i-del;
		if(j>0)s1.erase(s1.find(a[j]+j));
		s1.insert(a[i]+i);
	}
}
void dfs2(int u,int fa,int up){
	son[u].push_back(up);
	sort(son[u].begin(),son[u].end());
	reverse(son[u].begin(),son[u].end());
	int now=son[u][0];
	if(son[u].size()>1)now+=son[u][1];
	ans[u]=max(ans[u],now);
	for(int v:e[u])if(!inc[v]&&v!=fa){
		int now=son[u][0];
		assert(son[u].size()>1);
		if(now==mxd[v]+1)
			dfs2(v,u,max(up,son[u][1])+1);
		else dfs2(v,u,max(up,son[u][0])+1);
	}
}
void calc_circle(int *a,int n,int *id){
	for(int i=1;i<=n;i++)
		ans[id[i]]=max(ans[id[i]],a[i]);
	static int pre[N+5],suf[N+5];
	pre[0]=suf[n+1]=-(1<<29);
	for(int i=1;i<=n;i++)
		pre[i]=max(pre[i-1],a[i]-i);
	for(int i=n;i;i--)
		suf[i]=max(suf[i+1],a[i]+i);
	for(int i=1;i<=n;i++)
		ans[id[i]]=max({ans[id[i]],pre[i]+suf[i+1],pre[i-1]+suf[i]});
	int mxi=-(1<<29),mxj=-(1<<29);
	for(int i=1;i<=n;i++){
		mxj=max(mxj,mxi+a[i]-i+n);
		mxi=max(mxi,a[i]+i);
		ans[id[i]]=max(ans[id[i]],mxj);
	}
	mxi=mxj=-(1<<29);
	for(int i=n;i;i--){
		mxj=max(mxj,mxi+a[i]+i+n);
		mxi=max(mxi,a[i]-i);
		ans[id[i]]=max(ans[id[i]],mxj);
	}
}
int main(){
	n=read();int m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	if(n-1==m){
		dfs(1,0);
		dfs2(1,0,0);
		for(int i=1;i<=n;i++)
			printf("%d%c",ans[i],(i==n)?('\n'):(' '));
		return 0;
	}
	tarjan(1);
	memset(fa,0,sizeof(fa));
	for(int i=1;i<=cirlen;i++)dfs(id[i],0);
	for(int i=1;i<=cirlen;i++)a[i]=mxd[id[i]];
	calc_odis();
	for(int i=1;i<=cirlen;i++)dfs2(id[i],0,odis[id[i]]);
	calc_circle(a,cirlen,id);
	for(int i=1;i<=n;i++)
		printf("%d%c",ans[i],(i==n)?('\n'):(' '));
	return 0;
}