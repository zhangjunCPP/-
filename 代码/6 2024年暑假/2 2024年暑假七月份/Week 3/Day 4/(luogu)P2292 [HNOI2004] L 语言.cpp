#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int tree[N][26],tot;
int dep[N];
void insert(string s) {
	int now=0;
	int siz=s.size();
	for(int i=0;i<siz;i++) {
		int ch=s[i]-'a';
		if(!tree[now][ch])tree[now][ch]=++tot;
		now=tree[now][ch];
	}
	dep[now]=siz;
}
int fail[N];
int g[N];
void build() {
	queue<int>q;
	for(int i=0;i<26;i++)if(tree[0][i])q.push(tree[0][i]);
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(int i=0;i<26;i++) {
			if(tree[u][i])fail[tree[u][i]]=tree[fail[u]][i],q.push(tree[u][i]);
			else tree[u][i]=tree[fail[u]][i];
		}
	}
	for(int i=1;i<=tot;i++)for(int j=i;j;j=fail[j])if(dep[j])g[i]|=(1<<(dep[j]-1));
}
bool f[N];
int ask(string s) {
	int siz=s.size();
	int u=0;
	f[0]=true;
	int now=0;
	for(int i=1;i<=siz;i++) {
		u=tree[u][s[i-1]-'a'];
		now=((now<<1)|f[i-1])&((1<<10)-1);
		f[i]=(now&g[u])!=0;
	}
	for(int i=siz;i>=1;i--)if(f[i])return i;
	return 0;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		string s;
		cin>>s;
		insert(s);
	}
	build();
	while(m--) {
		string t;
		cin>>t;
		cout<<ask(t)<<"\n";
	}
}