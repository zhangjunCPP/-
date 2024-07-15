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
using namespace std;
typedef long long ll;
namespace FastIO {
	const int BUF_SIZ=1<<16;
	char in_buf[BUF_SIZ],*got_pos=in_buf,*read_pos=in_buf,out_buf[BUF_SIZ],*write_pos=out_buf;
	inline char get_next_char() {
		if(read_pos==got_pos) {
			got_pos=read_pos=in_buf;
			got_pos+=fread(got_pos,sizeof(char),BUF_SIZ, stdin);
		}
		return read_pos==got_pos?EOF:*(read_pos++);
	}
	inline void flush_output() {
		fwrite(out_buf,sizeof(char),write_pos-out_buf, stdout);
		write_pos=out_buf;
	}
	inline void put_char(char ch) {
		*(write_pos++)=ch;
		if(write_pos==out_buf+BUF_SIZ)
			flush_output();
	}
#define FASTIO_READ_NEGATIVE
#ifndef FASTIO_READ_NEGATIVE
template <typename T>
inline void read(T& res)
{
    char ch;
    while (!isdigit(ch = get_next_char()))
        ;
    res = ch ^ '0';
    while (isdigit(ch = get_next_char()))
        res = (res << 3) + (res << 1) + (ch ^ '0');
}
#else
	template<typename T>
	inline void read(T&res) {
		char ch;
		bool flg=0;
		while(!isdigit(ch=get_next_char()))
			flg|=ch=='-';
		res=ch^'0';
		while(isdigit(ch=get_next_char()))
			res=(res<<3)+(res<<1)+(ch^'0');
		if(flg)
			res=-res;
	}
#endif
	template<typename T>
	inline void write(T x) {
		if(!x) {
			put_char('0');
			return;
		}
		static int lis[25],*lp=lis;
		while(x) {
			*(++lp)=x%10;
			x/=10;
		}
		while(lp!=lis)
			put_char((*(lp--))+'0');
	}
	template<typename T>
	inline void writeln(const T&x) {
		write(x);
		put_char('\n');
	}
	template<typename T>
	inline void writesp(const T&x) {
		write(x);
		put_char(' ');
	}
	class _IO_Flusher {
	public:
		~_IO_Flusher() { flush_output(); }
	} __Flusher;
	class IStream {
	public:
		template<typename T>
		inline IStream&operator>>(T&x) {
			read(x);
			return *this;
		}
		inline IStream&operator>>(char*str) {
			char ch;
			while(isspace(ch=get_next_char()));
			(*(str++))=ch;
			while(!isspace(ch=get_next_char())) {
				if(ch==EOF)
					break;
				(*(str++))=ch;
			}
			*str=0;
			return *this;
		}
	} Cin;
	class OStream {
	public:
		template<typename T>
		inline enable_if_t<is_integral<T>::value,OStream&> operator<<(const T&x) {
			write(x);
			return *this;
		}
		inline OStream&operator<<(const char&ch) {
			put_char(ch);
			return *this;
		}
		inline OStream&operator<<(const char*str) {
			for(const char*p=str;*p;put_char(*(p++)));
			return *this;
		}
	} Cout;
}
using namespace FastIO;
#define cin Cin
#define cout Cout
constexpr int N=2e5+505,B=400,P=234074,mod=998244853;
constexpr int qpow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return res;
}
constexpr int iP=qpow(P,mod-2);
static_assert(1ll*P*iP%mod==1,"qwq");
// class Chunk0{
//     int n,a[N];
//     int query(int x) { int res=0; For(i,1,x) res=(res+a[i])%mod;; return res; }
// public:
//     void init(int _n) { n=_n; For(i,1,n) a[i]=0; }
//     void modify(int x,int y) { a[x]=y; }
//     int query(int l,int r) { return (query(r)-query(l-1)+mod)%mod; }
// }O1,O2,O3;
class Chunk1 {
	int n,a[N],s[N];
	int query(int x) {
		int res=0;
		For(i,0,x / B - 1) res=(res+s[i])%mod;;
		For(i,x / B * B,x) res=(res+a[i])%mod;;
		return res;
	}
public:
	void init(int _n) {
		n=_n;
		For(i,0,n) a[i]=s[i]=0;
	}
	void modify(int x,int y) {
		s[x/B]=(1ll*s[x/B]-a[x]+y+mod)%mod;
		a[x]=y;
	}
	int query(int l,int r) { return (query(r)-query(l-1)+mod)%mod; }
} O1,O2;
class Chunk2 {
	int n,a[N],s0[N],s1[N];
	int query(int x) { return ((x<B?0:s1[x/B-1])+s0[x])%mod; }
public:
	void init(int _n) {
		n=_n;
		For(i,0,n) a[i]=s0[i]=s1[i]=0;
	}
	void modify(int x,int y) {
		For(i,x / B,n / B) s1[i]=(1ll*s1[i]-a[x]+y+mod)%mod;;
		For(i,x,x / B * B + B - 1) s0[i]=(1ll*s0[i]-a[x]+y+mod)%mod;;
		a[x]=y;
	}
	int query(int l,int r) { return (query(r)-query(l-1)+mod)%mod; }
} O3;
int n,Q,a[N],qop[N],ql[N],qr[N],qx[N],pw[N],spw[N],ipw[N],ans[N];
signed main() {
	Fin("circle.in");
	Fout("circle.out");
	// Fin("circle1.in");
	atexit([]() { cerr<<"Time = "<<clock()<<" ms"<<endl; });
	cin>>n>>Q;
	For(i,1,n) {
		ll x;
		cin>>x;
		a[i]=(x%mod+mod)%mod;
	}
	For(i,1,Q) {
		cin>>qop[i];
		if(qop[i]==1) {
			ll x;
			cin>>ql[i]>>x;
			qx[i]=(x%mod+mod)%mod;
		} else {
			int K;
			cin>>ql[i]>>qr[i]>>K;
			qx[i]=qr[i]-ql[i]+1;
			while(K--) {
				int x;
				cin>>x;
				qx[i]=__gcd(qx[i],x);
			}
		}
	}
	pw[0]=1;
	For(i,1,n) pw[i]=1ll*pw[i-1]*P%mod;
	ipw[0]=1;
	For(i,1,n) ipw[i]=1ll*ipw[i-1]*iP%mod;
	spw[0]=1;
	For(i,1,n) spw[i]=(spw[i-1]+pw[i])%mod;
	For(k,1,B) {
		O1.init(n);
		For(i,1,n) O1.modify(i,1ll*a[i]*pw[i%k]%mod);
		O2.init(n);
		For(i,1,n / k) O2.modify(i,a[i*k]);
		For(id,1,Q) {
			if(qop[id]==1) {
				O1.modify(ql[id],1ll*qx[id]*pw[ql[id]%k]%mod);
				if(ql[id]%k==0)
					O2.modify(ql[id]/k,qx[id]);
			} else if(qx[id]==k) {
				int l=ql[id],r=qr[id];
				int s0=O2.query((l+k-1)/k,r/k);
				int ss=O1.query(l,r);
				ans[id]=(ss==1ll*s0*spw[k-1]%mod);
			}
		}
	}
	O3.init(n);
	For(i,1,n) O3.modify(i,1ll*a[i]*pw[i]%mod);
	For(id,1,Q) {
		if(qop[id]==1)
			a[ql[id]]=qx[id],O3.modify(ql[id],1ll*a[ql[id]]*pw[ql[id]]%mod);
		else if(qx[id]>B) {
			int l=ql[id],r=qr[id],k=qx[id];
			int ss=0,s0=0;
			For(i,(l + k - 1) / k,r / k) s0=(s0+a[i*k])%mod;
			For(i,(l - 1) / k,r / k) {
				int tl=max(l,i*k),tr=min(r,(i+1)*k-1);
				if(tl<=tr)
					ss=(ss+1ll*O3.query(tl,tr)*ipw[i*k])%mod;
			}
			ans[id]=(ss==1ll*s0*spw[k-1]%mod);
		}
	}
	For(i,1,Q) if(qop[i]==2)
		cout<<(ans[i]?"YES\n":"NO\n");
	// For(id,1,Q){
	//     if(qop[id]==1) a[ql[id]]=qx[id];
	//     else{
	//         int l=ql[id],r=qr[id],k=qx[id]; assert((r-l+1)%k==0);
	//         int s0=0; For(i,l,r) if(i%k==0) s0=(s0+a[i])%mod;
	//         int ss=0; For(i,l,r) ss=(ss+1ll*a[i]*pw[i%k])%mod;
	//         if(ss==1ll*s0*spw[k-1]%mod) cout<<"YES\n"; else cout<<"NO\n";
	//     }
	// }
	return 0;
}