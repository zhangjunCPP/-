#include<bits/stdc++.h>
#define IL inline
#define _ 100005
#define ll long long
using namespace std ;

IL int gi(){
	int data = 0 , m = 1; char ch = 0;
	while(ch!='-' && (ch<'0'||ch>'9')) ch = getchar();
	if(ch == '-'){m = 0 ; ch = getchar() ; }
	while(ch >= '0' && ch <= '9'){data = (data<<1) + (data<<3) + (ch^48) ; ch = getchar(); }
	return (m) ? data : -data ; 
}

int ans[_],par[18][_],up[18][_],dn[18][_],dep[_],oo,n,Q,dfn[_],ed[_],f[_],q[_],K,h[_],g[_] ;
bool cov[_] , In[_] ;
vector<int> son[_] ;
int _cnt ;
struct _Edge{int to , next ; } Edge[_ << 1] ; int head[_] , CNT , stk[_] ; int Ans ;
IL void AddEdge(int u , int v) {
	Edge[++ CNT] = (_Edge){v , head[u]} ; head[u] = CNT ; return ;
}

#define inf 1000000007

IL bool cmp_ans(int i , int j) {return ans[i] > ans[j] ; }
void dfs1(int u , int From , int deep) {
	ans[u] = 0 ; par[0][u] = From ; dfn[u] = ++ oo ; dep[u] = deep ;
	for(int e = 1; e <= 17; e ++) par[e][u] = par[e - 1][par[e - 1][u]] ;
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ;
		dfs1(v , u , deep + 1) ;
		ans[u] = max(ans[u] , ans[v] + 1) ; son[u].push_back(v) ; 
	}
	ed[u] = oo ; sort(son[u].begin() , son[u].end() , cmp_ans) ;
}
void dfs2(int u , int From , int fa_up , int fa_dn) {
	up[0][u] = fa_up ; dn[0][u] = fa_dn ;
	for(int e = 1; e <= 17; e ++) {
		up[e][u] = max(up[e - 1][u] , up[e - 1][par[e - 1][u]]) ;
		dn[e][u] = max(dn[e - 1][u] , dn[e - 1][par[e - 1][u]]) ; 
	}
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ; int t = 0 ;
		int ret1 = - dep[u] , ret2 = dep[u] ;
		for(int j = 0,lt = son[u].size(); j < lt; j ++) if(son[u][j] == v) ++ t ; else break ;
		if(t == son[u].size()) ;
		else ret1 = - dep[u] + ans[son[u][t]] + 1 , ret2 = dep[u] + ans[son[u][t]] + 1 ;
		dfs2(v , u , ret1 , ret2) ;
	}
	return ;
}

IL int GetLCA(int u , int v) {
	if(dep[u] < dep[v]) swap(u , v) ; int delta = dep[u] - dep[v] ;
	for(int e = 17; e >= 0; e --) if(delta & (1 << e)) u = par[e][u] ;
	if(u == v) return u ;
	for(int e = 17; e >= 0; e --)
		if(par[e][u] != par[e][v]) u = par[e][u] , v = par[e][v] ;
	return par[0][u] ;
}

void dfs3(int u , int From) {
	f[u] = cov[u] ? 0 : inf ; 
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ;
		dfs3(v , u) ; f[u] = min(f[u] , f[v] + dep[v] - dep[u]) ;
	}h[u] = f[u] ; return ;
}
void dfs4(int u , int From , int val_fa) {
	f[u] = min(f[u] , val_fa + dep[u]) ; g[u] = val_fa + dep[u] ; 
	int tmp[3] = {inf , inf , inf} ;
	if(cov[u]) tmp[0] = - dep[u] ;
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ; tmp[2] = f[v] + dep[v] - dep[u] - dep[u] ;
		sort(tmp , tmp + 2 + 1) ;
	}
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ; int t = f[v] + dep[v] - dep[u] - dep[u] ;
		if(t == tmp[0]) dfs4(v , u , min(val_fa , tmp[1])) ;
		else dfs4(v , u , min(val_fa , tmp[0])) ;
	}
	return ;
}
vector<int> Ban ;
void dfs5(int u , int From) {
	Ans = max(Ans , f[u]) ;
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ;
		int dis = dep[v] - dep[u] - 1 ;
		for(int e = 17; e >= 0; e --) if(dis & (1 << e)) v = par[e][v] ;
		In[v] = true ; Ban.push_back(v) ;
	}
	for(int j = 0,lt = son[u].size(); j < lt; j ++)
		if(!In[son[u][j]]) {
			Ans = max(Ans , ans[son[u][j]] + 1 + f[u]) ;
			break ;
		}
	for(int j = 0,lt = Ban.size(); j < lt; j ++) In[Ban[j]] = false ;
	Ban.clear() ;
	for(int e = head[u] ; e ; e = Edge[e].next) if(Edge[e].to != From) dfs5(Edge[e].to , u) ; return ;
}
/*
int Dfs1(int u , int From) {
	if(cov[u]) return 0 ;
	int dis = inf ;
	for(int e = head[u] ; e ;e  = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ;  
		dis = min(dis , Dfs1(v , u) + abs(dep[u] - dep[v])) ;
	}return dis ;
}
int Dfs2(int u , int From , int ban) {
	int dis = 0 ;
	for(int j = 0,lt = son[u].size(); j < lt; j ++) {
		int v = son[u][j] ; if(v != From&& v != ban) dis = max(dis , Dfs2(v , u , ban) + 1) ;
	}return dis ;
}
*/
IL void calc(int u , int fa , int H) {
	int dis = dep[u] - dep[fa] - 1 , x = u , v ;
	for(int e = 17; e >= 0; e --)
		if((1 << e) <= dis) {
			v = par[e][x] ;
			if(dep[u] - dep[v] + h[u] <= dep[v] - dep[fa] + H) {
				Ans = max(Ans , dep[u] + up[e][x] + h[u]) ; x = v ; dis -= (1 << e) ; 
			}
		}
	dis = dep[x] - dep[fa] - 1 ; if(!dis) return ;
	for(int e = 17; e >= 0; e --) if(dis & (1 << e)) Ans = max(Ans , - dep[fa] + dn[e][x] + H) , x = par[e][x] ;
	return ; 
}
void dfs6(int u , int From , int val_fa) {
	int tmp[3] = {inf , inf , inf} ;
	if(From && dep[u] - dep[From] != 1) calc(u , From , val_fa) ;
	for(int e = head[u] ; e ; e = Edge[e].next) {
		int v = Edge[e].to ; if(v == From) continue ; tmp[2] = f[v] + dep[v] - dep[u] ;
		sort(tmp , tmp + 2 + 1) ;
	} 
	for(int e = head[u] ; e ; e = Edge[e].next)
		if(Edge[e].to != From) {
			int v = Edge[e].to , vl = f[v] + dep[v] - dep[u] ;
			if(vl == tmp[0]) vl = tmp[1] ; else vl = tmp[0] ;
			if(cov[u]) vl = 0 ;
			dfs6(v , u , min(vl , g[u])) ; 
		}
	return ;
}

IL bool cmp_dfn(int i , int j) {return dfn[i] < dfn[j] ; }
int main() {
	freopen("master.in", "r", stdin);
	freopen("master.out", "w", stdout);
	n = gi() ; Q = gi() ;
	for(int i = 1,u,v; i < n; i ++) u = gi() , v = gi() , AddEdge(u , v) , AddEdge(v , u) ;
	dfs1(1 , 0 , 1) ;
	dfs2(1 , 0 , 0 , 0) ;
	memset(head , 0 , sizeof(head)) ; CNT = 0 ;
	f[0] = inf ;
	_cnt = 0 ; 
	while(Q --) {
		++ _cnt ; 
		K = gi() ; for(int i = 1; i <= K; i ++) q[i] = gi() ;
		for(int i = 1; i <= K; i ++) cov[q[i]] = true ;
		sort(q + 1 , q + K + 1 , cmp_dfn) ;
		for(int j = 1,lt = K; j < lt; j ++) q[++ K] = GetLCA(q[j] , q[j + 1]) ; q[++ K] = 1 ;
		sort(q + 1 , q + K + 1 , cmp_dfn) ;
		K = unique(q + 1 , q + K + 1) - q - 1 ;
		stk[0] = 0 ;
		for(int i = 1; i <= K; i ++) {
			while(stk[0] && ed[stk[stk[0]]] < dfn[q[i]]) -- stk[0] ;
			if(stk[0]) AddEdge(stk[stk[0]] , q[i]) , AddEdge(q[i] , stk[stk[0]]) ; stk[++ stk[0]] = q[i] ;
		}
		Ans = 0 ;
		dfs3(1 , 0) ;
		dfs4(1 , 0 , inf) ;
		dfs5(1 , 0) ;
		dfs6(1 , 0 , 0) ;
		printf("%d\n" , Ans) ; 
		for(int j = 1; j <= K; j ++) head[q[j]] = 0 , cov[q[j]] = false ; CNT = 0 ; 
	}
	return 0 ;
}

