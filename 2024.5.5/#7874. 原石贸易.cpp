#include "bits/stdc++.h"
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
using namespace std; typedef long long ll;
constexpr int N=1e5+5;
int n,a[N],s[N*2],P[N],Q[N];
class FTree{
    int n; ll c[N];
public:
    void init(int _n) { n=_n; For(i,1,n) c[i]=0; }
    void poke(int x,int y) { while(x<=n) { c[x]+=y; x+=x&(-x); } }
    ll peek(int x) { ll res=0; while(x) { res+=c[x]; x-=x&(-x); } return res; }
}T;
void solve(){
    cin>>n; For(i,1,n) cin>>a[i];
    For(i,1,n) s[i]=s[i-1]+a[i];; For(i,1,n) s[i+n]=s[i]+s[n];
    if(s[n]<0) return cout<<"-1\n",void();
    else if(s[n]==0) return cout<<(*max_element(a+1,a+1+n)==0?"0\n":"-1\n"),void();
    For(i,1,n) P[i]=s[i]>=0?s[i]/s[n]:-(-s[i]-1)/s[n]-1,Q[i]=s[i]-P[i]*s[n];
    ll ans=0; vector<int> tmp; For(i,1,n) tmp.push_back(s[i]);
    sort(tmp.begin(),tmp.end()); tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    int tcnt=tmp.size(); For(i,1,n) s[i]=lower_bound(tmp.begin(),tmp.end(),s[i])-tmp.begin()+1;
    T.init(tcnt); For(i,1,n) ans-=T.peek(s[i]-1),T.poke(s[i],P[i]+1);
    T.init(tcnt); Rev(i,n,1) ans-=T.peek(s[i]-1),T.poke(s[i],P[i]);
    static pair<int,int> p[N]; For(i,1,n) p[i]=make_pair(Q[i],s[i]);
    sort(p+1,p+1+n); T.init(tcnt);
    int j=1; for(int i=1;i<=n;i++){
        while(j<=n&&p[i].first>p[j].first) T.poke(p[j++].second,1);
        ans+=T.peek(p[i].second-1);
    }
    while(j<=n) T.poke(p[j++].second,1);
    For(i,1,n) ans+=T.peek(s[i]-1)*P[i];; cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); int Ti; cin>>Ti; while(Ti--) solve();; return 0;
}
