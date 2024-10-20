#include<bits/stdc++.h>
using namespace std;
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  template <class T>
  void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
  }

  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) { for (c = gc(); blank(c); c = gc()); }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  // 负数输出
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }

  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
int _lst = 0;
int get(){
    return _lst = ((_lst + 212001290) ^ 323920323) % 200 + 1;
}
// #define int long long
#define MAXN 300500
#define MAXL 20
const int P = 1e9 + 7;
int n,a[MAXN],k,b;

struct BlockQuery{
    static constexpr int B=350;
    int n,m;
    int bl[MAXN<<1],dl[MAXN<<1],dr[MAXN<<1];
    struct Block{
        int sum[B+10];
        int bsum;
        int tag;
        int st,ed;
    }b[MAXN/B+10];
    
    inline void init(int _n,int*a){
        static int tmp[MAXN<<1];
        n=_n;
        memcpy(tmp+1,a+1,sizeof(int)*n);
        m=ceil(1.0*n/B),n=m*B;
        
        for(int j=1;j<=m;j++) b[j].st=(j-1)*B+1,b[j].ed=j*B;
        for(int i=1;i<=n;i++) bl[i]=(i-1)/B+1;
        for(int i=1;i<=n;i++) dl[i]=i-b[bl[i]].st+1,dr[i]=b[bl[i]].ed-i+1;
        for(int i=1;i<=n;i++) b[bl[i]].sum[dl[i]]=(b[bl[i]].sum[dl[i]-1]+tmp[i])%P;
        for(int j=1;j<=m;j++) b[j].bsum=(b[j].sum[B]+b[j-1].bsum)%P;
    }  
    inline void Update(int lx,int rx,int v){
        Update(lx,v);
        Update(rx+1,-v);
    }
    inline void Update(int lx,int v){
        if(lx>n) return;
        // assert(v>=0);
        int tot=0,V=v,Bv=V*B;
        int k=bl[lx];
        for(int i=dl[lx];i<=B;i++){
            tot+=V;
            b[k].sum[i]=(b[k].sum[i]+tot)%P;
        }
        b[k].bsum=(b[k].bsum+tot)%P;
        for(int j=k+1;j<=m;j++){
            b[j].tag+=V;
            tot+=Bv;
            b[j].bsum=(b[j].bsum+tot)%P;
        }
    }
    inline int Query(int lx,int rx){
        return (Query(rx)-Query(lx-1)+P)%P;
    }
    inline int Query(int rx){
        int j=bl[rx],k=dl[rx];
        return rx?(b[j-1].bsum+b[j].sum[k]+1ll*b[j].tag*k)%P:0;
    }
}bit;
int del[MAXL][MAXN],ans[MAXL][MAXN],inv[MAXN];
int tmpsum[MAXL][MAXN];
void init(){
    bit.init(n,a);
    for(int i = 1;i <= n;i ++)a[i] += a[i-1];
    k = std::log2(n),b = k>>1,inv[1] = 1;
    for(int i = 2;i <= n;i ++)inv[i] = 1ll * (P - 1) * (P / i) % P * inv[P % i] % P;
    for(int i = n;i >= 1;i --)inv[i] = 1ll * inv[i] * inv[i - 1] % P;
    for(int i = 1;i <= b;i ++){
        int sz = 1 << i;
        for(int j = 1;j + sz - 1 <= n;j ++){
            del[i][j] = (0ll - a[j + sz - 1] + a[j + (sz >> 1) - 1] * 2 - a[j - 1] + P*2) % P;
            ans[i][j] = (1ll * del[i][j] * del[i][j] % P * inv[sz]  + ans[i-1][j] + ans[i-1][j+(sz>>1)]) % P;
        }
    }
}
#define get_delta(r,l0,r0) ((r) <= ( ((l0) + (r0)) >> 1) ? (r) - (l0) + 1 : (r0) - (r))
void m_add(int r,int v){
    for(int i = 1;i <= b;i ++){
        int sz = 1 << i;
        for(int j = max(r - sz + 1,1);j <= min(r,n - sz + 1);j ++){
            del[i][j] = (del[i][j] + get_delta(r,j,j + sz - 1) * v) % P;
            ans[i][j] = (1ll * del[i][j] * del[i][j] % P * inv[sz]  + ans[i-1][j] + ans[i-1][j+(sz>>1)]) % P;
        }
    }
}
int q_ans(int l,int r){
    int lg = std::log2(r - l + 1);
    long long ans = 0;
    for(int lg0 = min(lg,b),i = l;i <= r;i += (1 << lg0)){
        ans = (ans + ::ans[lg0][i]);
    }
    if(lg > b){
        for(int j = l;j <= r;j += (1 << (b))){
            tmpsum[b][j] = bit.Query(j,j+(1<<b)-1);
        }
        for(int i = b + 1;i <= lg;i ++){
            int sz = 1 << i;
            for(int j = l;j <= r;j += sz){
                tmpsum[i][j] = (tmpsum[i-1][j]+tmpsum[i-1][j+(sz>>1)]) % P;
                int del = ((tmpsum[i-1][j]-tmpsum[i-1][j+(sz>>1)])) % P;
                ans = (ans + 1ll *del * del % P * inv[sz] % P);
            }
        }
    }
    return ans % P;
}
signed main(){
    double nw = clock();
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int q,opt,x,y,z,lans = 0;
    io.read(n),io.read(q);
    for(int i = 1;i <= n;i ++)io.read(a[i]);
    init();
    while(q --){
        io.read(opt),io.read(x),io.read(y);
        opt ^= lans,x ^= lans,y ^= lans;
        assert(opt <= 2);
        if(opt == 1){
            z = get();
            bit.Update(x,y,z);
            m_add(y,z);
            if(x > 1)m_add(x - 1,- z);
        }else{
            io.write(lans = q_ans(x,y),'\n');
        }
    }
    //cerr << (clock() - nw) / CLOCKS_PER_SEC << "s\n";
}