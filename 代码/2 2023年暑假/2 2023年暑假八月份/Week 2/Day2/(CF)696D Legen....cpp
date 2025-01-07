#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=205;
int tree[N][26];
int fail[N],cnt;
int e[N];
void insert(string s,int v){
	int now=0;
	int SIZE=s.size();
	for(int i=0;i<SIZE;i++){
		if(!tree[now][s[i]-'a'])tree[now][s[i]-'a']=++cnt;
		now=tree[now][s[i]-'a'];
	}
	e[now]+=v;
}
queue<int>q;
void build(){
	for(int i=0;i<26;i++){
		if(tree[0][i]) {
			fail[tree[0][i]]=0;
			q.push(tree[0][i]);
		}
	}
	while(!q.empty()){
		int now=q.front();
		q.pop();
		e[now]+=e[fail[now]];
		for(int i=0;i<26;i++){
			if(tree[now][i]){
				fail[tree[now][i]]=tree[fail[now]][i];
				q.push(tree[now][i]);
			}
			else tree[now][i]=tree[fail[now]][i];
		}
	}
}
struct matrix{
	int a[N][N];
	void init(){memset(a,-0x3f,sizeof a);}
};
matrix mul(matrix a,matrix b){
	matrix ans;
	ans.init();
	for(int k=0;k<=cnt;k++)
		for(int i=0;i<=cnt;i++)
			for(int j=0;j<=cnt;j++){
				ans.a[i][j]=max(ans.a[i][j],a.a[i][k]+b.a[k][j]);
			}
	return ans;
}
matrix qpow(matrix x,int y){
	matrix ans;
	ans=x;
	y--;
	while(y){
		if(y&1)ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}
int val[N];
signed main(){
	int n,l;
	cin>>n>>l;
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		insert(s,val[i]);
	}
	build();
	matrix a;
	a.init();
	for(int i=0;i<=cnt;i++){
		for(int j=0;j<26;j++)a.a[i][tree[i][j]]=e[tree[i][j]];
	}
	matrix tmp=qpow(a,l);
	int ans=0;
	for(int i=0;i<=cnt;i++)ans=max(ans,tmp.a[0][i]);
	cout<<ans;
	return 0;
}