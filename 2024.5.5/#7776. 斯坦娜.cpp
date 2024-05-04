#include <bits/stdc++.h>
using namespace std;
// #define OPENIOBUF

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
constexpr LL INF=4e18;

#ifndef DADALZY
#define FILEIO(file) freopen(file".in","r",stdin),freopen(file".out","w",stdout)
#define LOG(...) void()
#else
#define FILEIO(file) freopen("ex_steiner2.in","r",stdin),freopen("output.out","w",stdout)
#define LOG(...) fprintf(stderr,__VA_ARGS__)
#endif

int n,m;
vector<pair<int,int>> G[200005];

LL dis1[200005],dis2[200005],dis3[200005];
void dijkstra(LL dis[])
{
	static bool vis[200005];
	priority_queue<pair<LL,int>,vector<pair<LL,int>>,greater<>> q;
	for(int i=1;i<=n;i++)
		if(dis[i]<INF) q.emplace(dis[i],i);
	fill(vis+1,vis+n+1,false);
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(auto &[v,w]: G[u])
		{
			LL tmp=dis[u]+w;
			if(tmp>=dis[v]) continue;
			q.emplace(dis[v]=tmp,v);
		}
	}
}

int main()
{
	qin>>n>>m;
	for(int i=1,u,v,w;i<=m;i++)
	{
		qin>>u>>v>>w;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	fill(dis1+1,dis1+n+1,INF);
	dis1[1]=0,dijkstra(dis1);
	fill(dis2+1,dis2+n+1,INF);
	dis2[2]=0,dijkstra(dis2);
	for(int i=1;i<=n;i++) dis3[i]=dis1[i]+dis2[i];
	dijkstra(dis3);
	qout.writesp(dis3+3,dis3+n+1);
	qout<<'\n';
	return 0;
}
