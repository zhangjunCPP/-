#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
using namespace std;
int wtop,wlen,wstk[40];
char rdc[1<<14],wtc[1<<23],*rS,*rT;
#define gc() (rS==rT?rT=(rS=rdc)+fread(rdc,1,1<<14,stdin),(rS==rT?EOF:*rS++):*rS++)
#define pc(x) wtc[wlen++]=(x)
#define flush() fwrite(wtc,1,wlen,stdout),wlen=0
template<class T=int>inline T read(){
    T x=0;char ch;bool f=0;
    while(!isdigit(ch=gc()))if(ch=='-')f=!f;
    do x=(x<<1)+(x<<3)+(ch^48);while(isdigit(ch=gc()));
    return f?-x:x;
}
inline int read(char*const s){
    char *t=s,ch;
    while(!isgraph(ch=gc()));
    do *t++=ch;while(isgraph(ch=gc()));
    return *t=0,t-s;
}
template<class T>inline void write(T x){
    if(wlen>=8000000)flush();
    if(!x)return pc('0'),void();
    if(x<0)pc('-'),x=-x;
    while(x)wstk[wtop++]=x%10,x/=10;
    while(wtop)pc(wstk[--wtop]^48);
}
inline void write(char*const s){
    if(wlen>=8000000)flush();
    for(int i=0;*(s+i);pc(*(s+(i++))));
}
inline void write(const char*s){
    if(wlen>=8000000)flush();
    for(int i=0;*(s+i);pc(*(s+(i++))));
}
typedef pair<int,int> PII;
const int N=5e5+5;
const LL INF=1e18+7;
int n,q,tim;
int d[N],lb[N],dfn[N],st[20][N];
int Gm,Gh[N],Gnxt[N];
inline void dfs(const int&u){
    for(int v=Gh[u];v;v=Gnxt[v])
        st[0][dfn[v]=++tim]=u,d[v]=d[u]+1,dfs(v);
}
inline int Min(const int&x,const int&y){
    return d[x]<d[y]?x:y;
}
inline int LCA(int x,int y){
    if(x==y)return x;
    x=dfn[x],y=dfn[y];
    if(x>y)swap(x,y);
    int t=lb[y-x];
    return Min(st[t][x+1],st[t][y-(1<<t)+1]);
}
inline int dist(const int&x,const int&y){
    return d[x]+d[y]-2*d[LCA(x,y)];
}
inline int exgcd(const int&a,const int&b,int&x,int&y){
    if(!b)return x=1,y=0,a;
    int d=exgcd(b,a%b,y,x);
    return y-=(a/b)*x,d;
}
inline LL cal1(const int&a,const int&b,const int&l,const int&r){
    int d=__gcd(l,r),c=b-a;
    if(c%d)return INF;
    int x,y;
    exgcd(l,r,x,y);
    int t=r/d;
    x=c/d*1ll*x%t,((x<0)&&(x+=t));
    return a+(LL)l*x;
}
inline LL sol2(const int&a,const int&b,const int&l,const int&r){
    if(!l||l>r)return 0;
    else if(!a)return INF;
    else if(r/a>(l-1)/a)return (l-1)/a+1;
    LL res=sol2(b%a,a,a-r%a,a-l%a);;
    return res>=INF?INF:((l+b*res-1)/a+1);
}
inline LL cal2(const int&a,const int&b,const int&l,const int&r,const int&d){
    if((a+b+d)&1)return INF;
    int L=(b-a-d)%r,R=(b-a+d)%r;
    ((L<0)&&(L+=r)),((R<0)&&(R+=r));
    LL p=(d*2==r?0:sol2(l,r,L,R));
    if(p>=INF)return INF;else p*=l;
    return (p+(p-b+a+d)/r*r+a+b+d)>>1;
}
inline LL solve(int u1,int v1,int u2,int v2){
    if(u2==v2)swap(u1,u2),swap(v1,v2);
    if(u1==v1){
        int d=dist(u2,u1);
        return d+dist(u1,v2)==dist(u2,v2)?d:-1;
    }
    static int p[4];
    p[0]=LCA(u1,u2),p[1]=LCA(u1,v2),p[2]=LCA(v1,u2),p[3]=LCA(v1,v2);
    sort(p,p+4,[&](int x,int y){return d[x]>d[y];});
    int p1=p[0],p2=p[1];
    if(p1==p2&&d[p1]<max(d[LCA(u1,v1)],d[LCA(u2,v2)]))return -1;
    int rd=dist(p1,p2),D1=dist(u1,v1)<<1,D2=dist(u2,v2)<<1;
    int R1=dist(u1,p1),R2=dist(u1,p2),R3=dist(u2,p1),R4=dist(u2,p2);
    if(R1>R2)R1+=dist(v1,p1)<<1;else R2+=dist(v1,p2)<<1;
    if(R3>R4)R3+=dist(v2,p1)<<1;else R4+=dist(v2,p2)<<1;
    LL ans=min(min(cal1(R1,R3,D1,D2),cal1(R2,R4,D1,D2)),min(cal2(R1,R4,D1,D2,rd),cal2(R2,R3,D1,D2,rd)));
    return ans>=INF?-1:ans;
}
signed main(){
    n=read(),q=read();
    for(int i=2;i<=n;++i)lb[i]=lb[i>>1]+1;
    for(int i=2;i<=n;++i){
        int fa=read();
        Gnxt[i]=Gh[fa],Gh[fa]=i;
    }
    dfs(1);
    for(int j=0,jj=1;jj<n;++j,jj<<=1)
        for(int i=1,ie=n-2*jj;i<=ie;++i)
            st[j+1][i]=Min(st[j][i],st[j][i+jj]);
    for(int i=1;i<=q;++i){
        int u1=read(),v1=read(),u2=read(),v2=read();
        write(solve(u1,v1,u2,v2)),pc('\n');
    }
    return flush();
}
