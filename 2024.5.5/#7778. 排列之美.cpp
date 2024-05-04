#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
	struct IO {
	    char ibuf[(1 << 20) + 1], *iS, *iT, obuf[(1 << 20) + 1], *oS;
	    IO() : iS(ibuf), iT(ibuf), oS(obuf) {} ~IO() { fwrite(obuf, 1, oS - obuf, stdout); }
		#if ONLINE_JUDGE
		#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
		#else
		#define gh() getchar()
		#endif
		inline bool eof (const char &ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == 't' || ch == EOF; }
	    inline long long read() {
	        char ch = gh();
	        long long x = 0;
	        bool t = 0;
	        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
	        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
	        return t ? ~(x - 1) : x;
	    }
	    inline void read (char *s) {
	    	char ch = gh(); int l = 0;
	    	while (eof(ch)) ch = gh();
	    	while (!eof(ch)) s[l++] = ch, ch = gh();
	    }
	    inline void read (double &x) {
	    	char ch = gh(); bool t = 0;
	    	while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
	    	while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gh();
	    	if (ch != '.') return t && (x = -x), void(); ch = gh();
	    	for (double cf = 0.1; '0' <= ch && ch <= '9'; ch = gh(), cf *= 0.1) x += cf * (ch ^ 48);
	    	t && (x = -x);
	    }
	    inline void pc (char ch) {
	    	#ifdef ONLINE_JUDGE
	    	if (oS == obuf + (1 << 20) + 1) fwrite(obuf, 1, oS - obuf, stdout), oS = obuf; 
	    	*oS++ = ch;
	    	#else
	    	putchar(ch);
	    	#endif
		}
		template<typename _Tp>
	    inline void write (_Tp x) {
	    	static char stk[64], *tp = stk;
	    	if (x < 0) x = ~(x - 1), pc('-');
			do *tp++ = x % 10, x /= 10;
			while (x);
			while (tp != stk) pc((*--tp) | 48);
	    }
	    inline void write (char *s) {
	    	int n = strlen(s);
	    	for (int i = 0; i < n; i++) pc(s[i]);
	    }
	} io;
	inline long long read () { return io.read(); }
	template<typename Tp>
	inline void read (Tp &x) { io.read(x); }
	template<typename _Tp>
	inline void write (_Tp x) { io.write(x); }
}
using namespace FastIO;
const int maxn=1e6+10,mod=998244353;
bool vis[maxn];
int n,m,a[maxn];
vector<int> vec;
void solve()
{
	n=read(),m=read();
    for(int i=1;i<=n;i++)vis[i]=0;
    for(int i=1;i<=m;i++)a[i]=read(),vis[a[i]]=1;
    vec.clear();
    vec.push_back(a[1]);
    bool flag=0;
    for(int i=1;i<m;i++)
    {
        vec.push_back(max(a[i],a[i+1]));
        if(a[i]>a[i+1]){flag=1;break;}
    }
    if(!flag)vec.push_back(a[m]);
    int ptr=0;
    int ans=1,val=0;
    for(int i=1;i<=n;i++)
        if(!vis[i])
        {
            while(ptr<vec.size()&&vec[ptr]<i)ptr++;
           //1 printf("%d %d\n",i,x);
            ans=1ll*ans*(ptr+val)%mod;
            val++;
        }
    write(ans),io.pc('\n');
}
int main()
{
//	freopen("ex_perm3.in","r",stdin);
    int T;
    T=read();
    while(T--)solve();
    return 0;
}
