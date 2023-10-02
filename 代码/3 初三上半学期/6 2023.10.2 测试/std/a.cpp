#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn=2e6+5, M=3e5;

ll n,m,q;
ll px[maxn], py[maxn], ans[maxn], sum[maxn], tag[maxn];

struct node {
    ll l;
    ll r;
    ll w;
    ll v;
};

struct matrix {
    ll lx;
    ll ly;
    ll rx;
    ll ry;
}a[maxn];

vector<node> g0,g1,g2,g3;
node t[maxn];

bool cmp(node x,node y) {
    return x.w<y.w;
}

void pushdown(ll x,ll l,ll r) {
    ll mid=l+r>>1;
    sum[x<<1]+=tag[x]*(mid-l+1), sum[x<<1|1]+=tag[x]*(r-mid);
    tag[x<<1]+=tag[x], tag[x<<1|1]+=tag[x], tag[x]=0;
    return ;
}

void modify(ll L,ll R,ll v,ll l,ll r,ll x) {
    if(L>R) swap(L,R);
    if(L<=l&&r<=R) {
        sum[x]+=(r-l+1)*v;
        tag[x]+=v;
        return ;
    }
    pushdown(x,l,r);
    ll mid=l+r>>1;
    if(L<=mid) modify(L,R,v,l,mid,x<<1);
    if(mid<R) modify(L,R,v,mid+1,r,x<<1|1);
    sum[x]=sum[x<<1]+sum[x<<1|1];
    return ; 
}

ll query(ll L,ll R,ll l,ll r,ll x) {
    if(L>R) swap(L,R);
    if(L<=l&&r<=R) return sum[x];
    pushdown(x,l,r);
    ll mid=l+r>>1, res=0;
    if(L<=mid) res+=query(L,R,l,mid,x<<1);
    if(mid<R) res+=query(L,R,mid+1,r,x<<1|1);
    return res;
}

void init() {
    memset(sum,0,sizeof(sum));
    memset(tag,0,sizeof(tag));
    return ;
}

void sol0() {
    init();
    for(ll i=1;i<=q;i++) t[i].l=px[i], t[i].r=py[i], t[i].w=py[i], t[i].v=i;
    sort(t+1,t+q+1,cmp), sort(g0.begin(),g0.end(),cmp);
    ll pos=0;
    for(ll i=1;i<=q;i++) {
        while(pos<g0.size()&&g0[pos].w<=t[i].w) {
            modify(g0[pos].l,g0[pos].r,g0[pos].v,1,M,1);
            pos++;
        }
        ans[t[i].v]+=query(1,t[i].l,1,M,1);
    }
    return ;
}

void sol1() {
    init();
    for(ll i=1;i<=q;i++) t[i].l=px[i], t[i].r=py[i], t[i].w=px[i]-py[i], t[i].v=i;
    sort(t+1,t+q+1,cmp), sort(g1.begin(),g1.end(),cmp);
    ll pos=0;
    for(ll i=1;i<=q;i++) {
        while(pos<g1.size()&&g1[pos].w<=t[i].w) {
            modify(g1[pos].l-g1[pos].w,g1[pos].r-g1[pos].w,g1[pos].v,1,M,1);
            pos++;
        }
        ans[t[i].v]+=query(1,t[i].r,1,M,1);
    }
    init();
    pos=g1.size()-1;
    for(ll i=q;i>=1;i--) {
        while(pos>=0&&g1[pos].w>t[i].w) {
            modify(g1[pos].l,g1[pos].r,g1[pos].v,1,M,1);
            pos--;
        }
        ans[t[i].v]+=query(1,t[i].l,1,M,1);
    }
    return ;
}

void sol2() {
    init();
    for(ll i=1;i<=q;i++) t[i].l=px[i], t[i].r=py[i], t[i].w=px[i], t[i].v=i;
    sort(t+1,t+q+1,cmp), sort(g2.begin(),g2.end(),cmp);
    ll pos=0;
    for(ll i=1;i<=q;i++) {
        while(pos<g2.size()&&g2[pos].w<=t[i].w) {
            modify(g2[pos].l,g2[pos].r,g2[pos].v,1,M,1);
            pos++;
        }
        ans[t[i].v]+=query(1,t[i].r,1,M,1);
    }
    return ;
}

void sol3() {
    init();
    for(ll i=1;i<=q;i++) t[i].l=px[i], t[i].r=py[i], t[i].w=px[i]+py[i], t[i].v=i;
    sort(t+1,t+q+1,cmp), sort(g3.begin(),g3.end(),cmp);
    ll pos=0, sum2=0;
    for(ll i=1;i<=q;i++) {
        while(pos<g3.size()&&g3[pos].w<=t[i].w) {
            modify(g3[pos].l,g3[pos].r,g3[pos].v,1,M,1);
            sum2+=(abs(g3[pos].l-g3[pos].r)+1)*g3[pos].v;
            pos++;
        }
        ans[t[i].v]+=sum2;
        ans[t[i].v]-=query(t[i].l+1,M,1,M,1);
    }
    init();
    pos=0;
    for(ll i=1;i<=q;i++) {
        while(pos<g3.size()&&g3[pos].w<=t[i].w) {
            modify(g3[pos].w-g3[pos].l,g3[pos].w-g3[pos].r,g3[pos].v,1,M,1);
            pos++;
        }
        ans[t[i].v]-=query(t[i].r+1,M,1,M,1);
    }
    return ;
}

int main() {
    
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>m>>q;
    for(ll i=1;i<=n;i++) cin>>a[i].lx>>a[i].ly>>a[i].rx>>a[i].ry, a[i].rx++, a[i].ry++;
    for(ll i=1;i<=m;i++) {
        ll type,r,d; cin>>type>>r>>d;
        ll tp=type%4; d--;
        if(type>=4) d=-d;
        if(tp==0) {
            g0.push_back((node){a[r].lx,a[r].lx+d,a[r].ly,1});
            g0.push_back((node){a[r].lx,a[r].lx+d,a[r].ry,-1});
            g0.push_back((node){a[r].rx,a[r].rx+d,a[r].ly,-1});
            g0.push_back((node){a[r].rx,a[r].rx+d,a[r].ry,1});
            if(type>=4) d--;
            else d++;
            a[r].lx+=d, a[r].rx+=d;
        }
        if(tp==1) {
            g1.push_back((node){a[r].lx,a[r].lx+d,a[r].lx-a[r].ly,1});
            g1.push_back((node){a[r].lx,a[r].lx+d,a[r].lx-a[r].ry,-1});
            g1.push_back((node){a[r].rx,a[r].rx+d,a[r].rx-a[r].ly,-1});
            g1.push_back((node){a[r].rx,a[r].rx+d,a[r].rx-a[r].ry,1});
            if(type>=4) d--;
            else d++;
            a[r].lx+=d, a[r].rx+=d, a[r].ly+=d, a[r].ry+=d;
        }
        if(tp==2) {
            g2.push_back((node){a[r].ly,a[r].ly+d,a[r].lx,1});
            g2.push_back((node){a[r].ly,a[r].ly+d,a[r].rx,-1});
            g2.push_back((node){a[r].ry,a[r].ry+d,a[r].lx,-1});
            g2.push_back((node){a[r].ry,a[r].ry+d,a[r].rx,1});
            if(type>=4) d--;
            else d++;
            a[r].ly+=d, a[r].ry+=d;
        }
        if(tp==3) {
            g3.push_back((node){a[r].lx,a[r].lx-d,a[r].lx+a[r].ly,1});
            g3.push_back((node){a[r].lx,a[r].lx-d,a[r].lx+a[r].ry,-1});
            g3.push_back((node){a[r].rx,a[r].rx-d,a[r].rx+a[r].ly,-1});
            g3.push_back((node){a[r].rx,a[r].rx-d,a[r].rx+a[r].ry,1});
            if(type>=4) d--;
            else d++;
            a[r].lx-=d, a[r].rx-=d, a[r].ly+=d, a[r].ry+=d;
        }
    }
    for(ll i=1;i<=n;i++) {
        g0.push_back((node){a[i].lx,a[i].lx,a[i].ly,1});
        g0.push_back((node){a[i].lx,a[i].lx,a[i].ry,-1});
        g0.push_back((node){a[i].rx,a[i].rx,a[i].ly,-1});
        g0.push_back((node){a[i].rx,a[i].rx,a[i].ry,1});
    }
    for(ll i=1;i<=q;i++) cin>>px[i]>>py[i];
    sol0(), sol1(), sol2(), sol3();
    for(ll i=1;i<=q;i++) cout<<ans[i]<<'\n'; cout<<'\n';
    return 0;
}
