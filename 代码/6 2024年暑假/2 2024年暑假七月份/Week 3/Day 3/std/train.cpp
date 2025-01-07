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
#ifndef FASTIO_READ_NEGATIVE
	template<typename T>
	inline void read(T&res) {
		char ch;
		while(!isdigit(ch=get_next_char()));
		res=ch^'0';
		while(isdigit(ch=get_next_char()))
			res=(res<<3)+(res<<1)+(ch^'0');
	}
#else
template <typename T>
inline void read(T& res)
{
	char ch;
	bool flg = 0;
	while (!isdigit(ch = get_next_char()))
		flg |= ch == '-';
	res = ch ^ '0';
	while (isdigit(ch = get_next_char()))
		res = (res << 3) + (res << 1) + (ch ^ '0');
	if (flg)
		res = -res;
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
constexpr int N=1e5+5,M=1e7+5;
struct Node {
	Node*lc,*rc;
	int mx;
	void update() {
		assert(lc || rc);
		mx=0;
		if(lc)
			mx=max(mx,lc->mx);
		if(rc)
			mx=max(mx,rc->mx);
	}
	static void insert(Node*&u,int d,int x,int o) {
		if(!u)
			u=new Node;
		if(d==-1)
			return u->mx=max(u->mx,o),void();
		insert(~x>>d&1?u->lc:u->rc,d-1,x,o);
		u->update();
	}
	int query(int d,int x,int o) {
		if(d==-1)
			return assert(mx >= o),mx;
		if(~x>>d&1) {
			if(rc&&rc->mx>=o)
				return rc->query(d-1,x,o);
			else
				return lc->query(d-1,x,o);
		} else {
			if(lc&&lc->mx>=o)
				return lc->query(d-1,x,o);
			else
				return rc->query(d-1,x,o);
		}
	}
	int query2(int d,int x,int o) {
		if(d==-1)
			return 0;
		if(~o>>d&1) {
			if(~x>>d&1)
				return max(lc?lc->query2(d-1,x,o):0,rc?rc->mx:0);
			else
				return max(rc?rc->query2(d-1,x,o):0,lc?lc->mx:0);
		} else {
			if(~x>>d&1)
				return rc?rc->query2(d-1,x,o):0;
			else
				return lc?lc->query2(d-1,x,o):0;
		}
	}
	static Node __pool[M];
	static int __poolcnt;
	static void poolReset() { __poolcnt=0; }
	void*operator new(size_t) {
		Node*res=&__pool[++__poolcnt];
		assert(__poolcnt < M);
		res->lc=res->rc=0;
		res->mx=0;
		return res;
	}
};
Node Node::__pool[M];
int Node::__poolcnt=0;
using tiii=tuple<int,int,int>;
int n,Q,a[N],ans[N],fa[N][20],mx[N][20];
void solve(int l,int r,vector<tiii> lis) {
	if(l==r)
		return;
	int mid=(l+r)>>1;
	Node::poolReset();
	Node*rt=new Node;
	For(i,mid + 1,r) {
		if(i!=mid+1)
			fa[i][0]=rt->query(29,a[i],0);
		else
			fa[i][0]=0;
		Node::insert(rt,29,a[i],i);
	}
	Node::poolReset();
	rt=new Node;
	For(i,l,mid) rt->insert(rt,29,a[i],i);
	For(i,mid + 2,r) mx[i][0]=rt->query2(29,a[i],a[i]^a[fa[i][0]]);
	For(j,1,__lg(r - mid + 1))
		For(i,mid + 1,r)
			if(fa[i][j-1]) fa[i][j]=fa[fa[i][j-1]][j-1],mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
			else fa[i][j]=0;
	vector<tiii> lisL,lisR;
	for(auto [x, y, id]:lis) {
		if(y<=mid)
			lisL.emplace_back(x,y,id);
		else if(mid<x)
			lisR.emplace_back(x,y,id);
		else {
			Rev(i,__lg(r - mid + 1),0)
				if(fa[y][i]&&mx[y][i]<x) {
					ans[id]+=1<<i;
					y=fa[y][i];
				}
			ans[id]++;
			y=rt->query(29,a[y],x);
			lisL.emplace_back(x,y,id);
		}
	}
	solve(l,mid,lisL);
	solve(mid+1,r,lisR);
}
void Main() {
	static int kase=0;
	debug(++kase);
	cin>>n>>Q;
	For(i,1,n)
		cin>>a[i];
	vector<tiii> lis;
	For(i,1,Q) {
		int l,r;
		cin>>l>>r;
		lis.emplace_back(l,r,i);
		ans[i]=0;
	}
	solve(1,n,lis);
	For(i,1,Q)
		cout<<ans[i]<<'\n';
}
signed main() {
	freopen("train.in","r", stdin);
	freopen("train.out","w", stdout);
	atexit([]() { cerr<<"Time = "<<clock()<<" ms"<<endl; });
	int T;
	cin>>T;
	while(T--)
		Main();
	return 0;
}