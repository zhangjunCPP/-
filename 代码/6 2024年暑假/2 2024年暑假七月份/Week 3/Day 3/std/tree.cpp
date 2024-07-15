#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) []() {}()
#define debuga(...) []() {}()
#endif
#define For(i, a, b) for (int i = a; i <= b; i++)
#define Rev(i, a, b) for (int i = a; i >= b; i--)
#define Fin(file) freopen(file, "r", stdin)
#define Fout(file) freopen(file, "w", stdout)
#define fi first
#define se second
using namespace std;
typedef long long ll;
constexpr int N=2e5+5,mod=998244353;
struct Node {
	Node*lc,*rc,*fa;
	int type,A,B;
	int cntA,cntB,cntP,tmpA,sum;
	void build(int _type,Node*_lc,Node*_rc) {
		lc=_lc;
		rc=_rc;
		lc->fa=rc->fa=this;
		type=_type;
		if(type==1)
			A=lc->A,B=rc->B;
		else
			A=lc->A,B=lc->B;
	}
	void set() {
		assert(!lc && !rc);
		cntA=1;
		cntB=1;
		cntP=1;
		tmpA=0;
		sum=1;
	}
	void update() {
		if(type==1) {
			cntA=(lc->cntA+1ll*lc->cntP*(rc->cntA+rc->tmpA+1ll*rc->cntA*rc->tmpA%mod))%mod;
			cntB=(rc->cntB+1ll*rc->cntP*(rc->tmpA+1)%mod*lc->cntB)%mod;
			cntP=1ll*rc->cntP*lc->cntP%mod*(rc->tmpA+1)%mod;
			tmpA=lc->tmpA;
			sum=(lc->sum+rc->sum+(rc->cntA+rc->tmpA+1ll*rc->cntA*rc->tmpA)%mod*lc->cntB)%mod;
		} else {
			cntA=lc->cntA;
			cntB=lc->cntB;
			cntP=lc->cntP;
			tmpA=(1ll*(lc->tmpA+1)*(rc->cntA+1)%mod*(rc->tmpA+1)-1+mod)%mod;
			sum=(lc->sum+rc->sum)%mod;
		}
	}
	// void print(){
	//     debug(type,A,B,cntA,cntB,cntP,sum,lc-__pool,rc-__pool);
	// }
	static Node __pool[N*2];
	static int __poolcnt;
	void*operator new(size_t) {
		return &__pool[++__poolcnt];
	}
};
Node Node::__pool[N*2];
int Node::__poolcnt=0;
Node*O[N];
int n,m,a[N],siz[N],son[N],ans[N];
vector<int> to[N];
Node*Bundle(int type,vector<pair<int,Node*>>::iterator Lp,vector<pair<int,Node*>>::iterator Rp) {
	if(Lp+1==Rp)
		return Lp->se;
	auto Mid=lower_bound(Lp,Rp,make_pair((Lp->fi+prev(Rp)->fi)/2,(Node*)(0)));
	if(Mid==Lp)
		Mid++;;
	if(Mid==Rp)
		Mid--;
	Node*lc=Bundle(type,Lp,Mid),*rc=Bundle(type,Mid,Rp);
	Node*res=new Node;
	res->build(type,lc,rc);
	return res;
}
void dfs1(int u,int pa) {
	siz[u]=1;
	for(int v:to[u])
		if(v!=pa) {
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
}
Node*dfs2(int u,int pa) {
	O[u]=new Node;
	O[u]->A=pa;
	O[u]->B=u;
	vector<pair<int,Node*>> lis;
	lis.emplace_back(1,O[u]);
	for(int w=u,lst=pa;son[w];lst=w,w=son[w]) {
		O[son[w]]=new Node;
		O[son[w]]->A=w;
		O[son[w]]->B=son[w];
		vector<pair<int,Node*>> tmp;
		tmp.emplace_back(1,O[son[w]]);
		for(int v:to[w])
			if(v!=lst&&v!=son[w])
				tmp.emplace_back(tmp.back().fi+siz[v],dfs2(v,w));
		lis.emplace_back(lis.back().fi+tmp.back().fi,Bundle(2,tmp.begin(),tmp.end()));
	}
	return Bundle(1,lis.begin(),lis.end());
}
signed main() {
	freopen("tree.in","r", stdin);
	freopen("tree.out","w", stdout);
	atexit([]() { cerr<<"Time = "<<clock()<<" ms"<<endl; });
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	For(i,1,n) cin>>a[i];;
	For(i,1,n - 1) {
		int x,y;
		cin>>x>>y;
		to[x].push_back(y);
		to[y].push_back(x);
	}
	dfs1(1,0);
	Node*rt=dfs2(1,0);
	// For(i,1,Node::__poolcnt) Node::__pool[i].print();
	static vector<int> lis[N];
	For(i,1,n) lis[a[i]].push_back(i);
	For(i,1,m) {
		for(int u:lis[i]) {
			O[u]->set();
			for(auto o=O[u]->fa;o;o=o->fa)
				o->update();
		}
		// debug(i);
		// For(i,1,Node::__poolcnt) Node::__pool[i].print();
		ans[i]=rt->sum;
	}
	debuga(ans,1,m);
	For(i,1,m) cout<<(ans[i]-ans[i-1]+mod)%mod<<' ';;
	cout<<'\n';
	return 0;
}