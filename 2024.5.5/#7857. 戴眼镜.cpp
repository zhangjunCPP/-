#include "bits/stdc++.h"
#ifdef DEBUG
#include "PrettyDebug.hpp"
#else
#define debug(...) [](auto...){}(__VA_ARGS__)
#endif
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define Fin(file) freopen(file,"r",stdin)
#define Fout(file) freopen(file,"w",stdout)
#define assume(expr) ((!!(expr))||(exit((fprintf(stderr,"Assumption Failed: %s on Line %d\n",#expr,__LINE__),-1)),false))
#define range basic_string_view
using namespace std; typedef long long ll;
struct Node{
    ll l,r,t,mn;
    friend Node operator+ (const Node& A,const Node& B){
        return Node{min(A.l,A.t+B.l),min(B.r,B.t+A.r),A.t+B.t,min({A.mn,B.mn,A.r+B.l})};
    }
    void set(ll x) { l=r=mn=min(x,0ll); t=x; }
};
class STree{
    int n; vector<Node> a; vector<ll> p; vector<int> tmp;
    #define k1 k<<1
    #define k2 k<<1|1
    void build(int k,int l,int r,int K){
        if(l==r){
            if(l&1) return a[k].set(p[l]=K),void();
            else return a[k].set(1ll*(tmp[l/2+1]-tmp[l/2]-1)*K),void();
        }
        int mid=(l+r)>>1; build(k1,l,mid,K); build(k2,mid+1,r,K); a[k]=a[k1]+a[k2];
    }
    void modify(int k,int l,int r,int x,int y){
        if(l==r) return a[k].set(p[l]+=y),void();
        int mid=(l+r)>>1; x<=mid?modify(k1,l,mid,x,y):modify(k2,mid+1,r,x,y); a[k]=a[k1]+a[k2];
    }
public:
    STree(int K,const vector<int>& _tmp) { tmp=_tmp; n=2*(tmp.size()-1)-1; a.resize((n<<2)+1); p.resize(n+1); build(1,1,n,K); }
    void modify(int x,int y) { modify(1,1,n,x*2-1,y); }
    Node query() { return a[1]; }
};
signed main(){
    // Fin("glass.in"); Fout("glass.out");
    atexit([](){cerr<<"Time = "<<clock()<<" ms"<<endl;}); ios::sync_with_stdio(0); cin.tie(0);
    int n,Q,K,D; cin>>n>>Q>>K>>D; vector<int> tmp(1); vector<pair<int,int>> qry;
    For(_,1,Q) { int x,y; cin>>x>>y; qry.emplace_back(x,y); tmp.push_back(x); }
    tmp.push_back(n); sort(tmp.begin()+1,tmp.end()); tmp.erase(unique(tmp.begin()+1,tmp.end()),tmp.end());
    STree T(K,tmp);
    for(auto [x,y]:qry){
        T.modify(lower_bound(tmp.begin()+1,tmp.end(),x)-tmp.begin(),-y); Node res=T.query();
        cout<<(res.mn>=-1ll*K*D&&res.r>=0?"Yes\n":"No\n");
    }
    return 0;
}
