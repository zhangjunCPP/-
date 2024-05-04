#include <bits/stdc++.h>
using namespace std;
#define OPENIOBUF

namespace FastIO
{

class FastIOBase
{
 protected:
#ifdef OPENIOBUF
	static const int BUFSIZE=1<<16;
	char buf[BUFSIZE+1];
	int buf_p=0;
#endif
	FILE *target;
	FastIOBase(FILE *f): target(f){}
	~FastIOBase()=default;
 public:
#ifdef OPENIOBUF
	virtual void flush()=0;
#endif
};

class FastOutput final: public FastIOBase
{
 private:
	void __putc(char x)
	{
#ifdef OPENIOBUF
		if(buf[buf_p++]=x,buf_p==BUFSIZE) flush();
#else
		putc(x,target);
#endif
	}
	template<typename T>
	void __write(T x)
	{
		char stk[64],*top=stk;
		if(x<0) return __putc('-'),__write(-x);
		do *(top++)=x%10,x/=10; while(x);
		for(;top!=stk;__putc(*(--top)+'0'));
	}
 public:
	FastOutput(FILE *f=stdout): FastIOBase(f) {}
#ifdef OPENIOBUF
	~FastOutput() { flush(); }
	void flush() { fwrite(buf,1,buf_p,target),buf_p=0; }
#endif
	FastOutput &operator <<(char x)
	{ return __putc(x),*this; }
	FastOutput &operator <<(const char *s)
	{ for(;*s;__putc(*(s++)));return *this; }
	FastOutput &operator <<(const std::string &s)
	{ return (*this)<<s.c_str(); }
	template<typename T>
	std::enable_if_t<std::is_integral<T>::value,FastOutput&> operator <<(const T &x)
	{ return __write(x),*this; }
	template<typename ...T>
	void writesp(const T &...x)
	{ std::initializer_list<int>{(this->operator<<(x),__putc(' '),0)...}; }
	template<typename ...T>
	void writeln(const T &...x)
	{ std::initializer_list<int>{(this->operator<<(x),__putc('\n'),0)...}; }
	template<typename Iter>
	void writesp(Iter begin,Iter end)
	{ while(begin!=end) (*this)<<*(begin++)<<' '; }
	template<typename Iter>
	void writeln(Iter begin,Iter end)
	{ while(begin!=end) (*this)<<*(begin++)<<'\n'; }
}qout;

class FastInput final: public FastIOBase
{
 private:
	bool __eof;
 public:
	FastInput(FILE *f=stdin): FastIOBase(f),__eof(false)
#ifdef OPENIOBUF
	{ buf_p=BUFSIZE; }
	void flush() { buf[fread(buf,1,BUFSIZE,target)]=EOF,buf_p=0; }
	bool eof()const { return buf[buf_p]==EOF; }
#else
	{}
	bool eof()const { return feof(target); }
#endif
	char get()
	{
		if(__eof) return EOF;
#ifdef OPENIOBUF
		if(buf_p==BUFSIZE) flush();
		char ch=buf[buf_p++];
#else
		char ch=getc(target);
#endif
		return ~ch?ch:(__eof=true,EOF);
	}
	void unget(char c)
	{
		__eof=false;
#ifdef OPENIOBUF
		buf_p--;
#else
		ungetc(c,target);
#endif
	}
	explicit operator bool()const { return !__eof; }
	FastInput &operator >>(char &x)
	{ while(isspace(x=get()));return *this; }
	template<typename T>
	std::enable_if_t<std::is_integral<T>::value,FastInput&> operator >>(T &x)
	{
		char ch,sym=0;x=0;
		while(isspace(ch=get()));
		if(__eof) return *this;
		if(ch=='-') sym=1,ch=get();
		for(x=0;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=get());
		return unget(ch),sym?x=-x:x,*this;
	}
	FastInput &operator >>(char *s)
	{
		while(isspace(*s=get()));
		if(__eof) return *this;
		for(;!isspace(*s) && !__eof;*(++s)=get());
		return unget(*s),*s='\0',*this;
	}
	FastInput &operator >>(std::string &s)
	{
		char str_buf[(1<<8)+1]={0},*p=str_buf;
		char *const buf_end=str_buf+(1<<8);
		while(isspace(*p=get()));
		if(__eof) return *this;
		for(s.clear(),p++;;p=str_buf)
		{
			for(;p!=buf_end && !isspace(*p=get()) && !__eof;p++);
			if(p!=buf_end) break;
			s.append(str_buf);
		}
		unget(*p),*p='\0',s.append(str_buf);
		return *this;
	}
	template<typename ...T>
	void read(T &...x)
	{ std::initializer_list<int>{(this->operator>>(x),0)...}; }
	template<typename Iter>
	void read(Iter begin,Iter end)
	{ while(begin!=end) (*this)>>*(begin++); }
}qin;

} // namespace FastIO
using FastIO::qin,FastIO::qout;

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

#ifndef DADALZY
#define FILEIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define LOG(...) void()
#else
#define FILEIO(file) freopen("5-16.in","r",stdin)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

namespace Math
{

template<typename Derived>
class ModintBase
{
 protected:
	int val;
 private:
	template<typename T>
	constexpr enable_if_t<is_integral<T>::value,T> __inv(T a,T b)const
	{ T x=0,y=1,t=0;for(;a;t=b/a,std::swap(a,b-=t*a),std::swap(y,x-=t*y));return x; }
	template<typename T>
	constexpr enable_if_t<is_integral<T>::value,T> __fix(T x)const
	{ return static_cast<const Derived*>(this)->fix(x); }
	constexpr static ModintBase __unfixed(int x)
	{ return reinterpret_cast<ModintBase&>(x); }
#define DEF_OP1(op) \
	friend constexpr ModintBase operator op(const ModintBase &lhs,const ModintBase &rhs)\
	{ return ModintBase(lhs)op##=rhs; }\
	ModintBase &operator op##=(const ModintBase &rhs)
#define DEF_OP2(op) \
	constexpr ModintBase  operator op(int)\
	{ ModintBase res(*this);return op(*this),res; }\
	constexpr ModintBase &operator op()
#define DEF_OP3(op) \
	constexpr ModintBase operator op()const
#define DEF_OP4(op) \
	friend constexpr bool operator op(const ModintBase &lhs,const ModintBase &rhs) \
	{ return lhs.val op rhs.val; }
#define MOD static_cast<const Derived*>(this)->getMod()
 public:
	constexpr ModintBase(): val(0) {}
	template<typename T>
	constexpr ModintBase(const T &x): val(__fix(x)) {}
	constexpr int operator ()()const { return val; }
	DEF_OP1(+) { return (val+=rhs.val)>=MOD?val-=MOD:0,*this; }
	DEF_OP1(-) { return (val-=rhs.val)<0?val+=MOD:0,*this; }
	DEF_OP1(*) { return val=__fix(1ll*val*rhs.val),*this; }
	DEF_OP1(/) { return val=__fix(1ll*val*__inv(rhs.val,MOD)),*this; }
	DEF_OP2(++) { return (++val)>=MOD?val-=MOD:0,*this; }
	DEF_OP2(--) { return (--val)<0?val+=MOD:0,*this; }
	DEF_OP3(+) { return *this; }
	DEF_OP3(-) { return __unfixed(val?MOD-val:0); }
	DEF_OP4(==) DEF_OP4(!=) DEF_OP4(<) DEF_OP4(>) DEF_OP4(<=) DEF_OP4(>=)
	constexpr ModintBase inv()const
	{ return ModintBase(__inv(val,MOD)); }
	template<typename T>
	friend inline constexpr enable_if_t<is_integral<T>::value,Derived> qpow(Derived x,T y)
	{ Derived res(1);for(;y;x*=x,y>>=1)if(y&1)res*=x;return res; }
#undef DEF_OP1
#undef DEF_OP2
#undef DEF_OP3
#undef DEF_OP4
#undef MOD
};

class FastMod
{
 private:
	using ULL=uint64_t;
	using U128=__uint128_t;
	ULL p,m;
 public:
	constexpr FastMod(): p(0),m(0) {}
	constexpr FastMod(ULL p): p(p),m((U128(1)<<64)/p) {}
	constexpr ULL getp()const { return p; }
	constexpr ULL operator()(ULL a)const
	{ ULL q=(U128(m)*a)>>64,r=a-q*p;return r>=p?r-p:r; }
};

// Modint for dynamic MOD
class DModint: public ModintBase<DModint>
{
 private:
	using BaseT=ModintBase<DModint>;
	static FastMod R;
	friend BaseT;
	template<typename T> static constexpr T fix(T x)
	{ return x<0?R.getp()-R(-x):R(x); }
 public:
	template<typename ...T>
	constexpr DModint(T ...x): BaseT(x...){}
	static constexpr void setMod(int mod) { R=FastMod(mod); }
	static constexpr int getMod() { return R.getp(); }
};
FastMod DModint::R{};

// Modint for static MOD
template<int MOD>
class SModint: public ModintBase<SModint<MOD>>
{
 private:
	using BaseT=ModintBase<SModint<MOD>>;
	friend BaseT;
	template<typename T> static constexpr T fix(T x)
	{ return (x%=MOD)<0?x+MOD:x; }
 public:
	template<typename ...T>
	constexpr SModint(T ...x): BaseT(x...) {}
	static constexpr int getMod() { return MOD; }
};

} // namespace Math

constexpr int MOD=998244353;
using Mint=Math::SModint<MOD>;

int n,m,k;
struct Edge{ int u,v,w; }e[300005];

vector<int> G[200005];
int nn,fa[200005],lc[200005],rc[200005],val[200005];
inline int findFa(int x)
{ return x!=fa[x]?fa[x]=findFa(fa[x]):x; }
void dfs1(int u,int tp)
{
	if(val[u]!=val[tp])
		G[tp].push_back(u),tp=u;
	if(u<=n) return;
	dfs1(lc[u],tp),dfs1(rc[u],tp);
}
using Poly=vector<Mint>;
Poly mul(const Poly &A,const Poly &B)
{
	int n=A.size(),m=B.size();
	Poly res(min(n+m-1,k+1));
	for(int i=0;i<n;i++)
		for(int j=0;j<m && i+j<=k;j++)
			res[i+j]+=A[i]*B[j];
	return res;
}
Poly dfs2(int u)
{
	Poly res{1,0};
	for(auto &v: G[u]) res=mul(res,dfs2(v));
	if(u>n && G[u].size()<res.size())
		res[G[u].size()]--;
	res[1]++;
	return res;
}

int main()
{
	qin>>n>>m>>k;
	for(int i=1;i<=m;i++)
		qin>>e[i].u>>e[i].v>>e[i].w;
	sort(e+1,e+m+1,[](auto &x,auto &y){ return x.w<y.w; });
	iota(fa+1,fa+2*n,1);
	nn=n;
	for(int i=1;i<=m;i++)
	{
		int u=findFa(e[i].u),v=findFa(e[i].v);
		if(u==v) continue;
		val[++nn]=e[i].w;
		fa[u]=fa[v]=nn;
		lc[nn]=u,rc[nn]=v;
	}
	Poly f{1};
	for(int v=1;v<=nn;v++)
		if(fa[v]==v) dfs1(v,v),f=mul(f,dfs2(v));
	Mint ans;
	for(auto &i: f) ans+=i;
	qout<<ans()<<'\n';
	return 0;
}
