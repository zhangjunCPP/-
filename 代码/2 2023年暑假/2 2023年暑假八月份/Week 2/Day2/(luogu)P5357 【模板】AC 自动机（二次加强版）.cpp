#include <bits/stdc++.h>

using namespace std;
const int N=1e6+10;
int tree[N][30];
int fail[N];
int cnt;
int e[N];
void insert(string s,int id){
	int now=0;
	int SIZE=s.size();
	for(int i=0;i<SIZE;i++){
		if(!tree[now][s[i]-'a']) tree[now][s[i]-'a']=++cnt;
		now=tree[now][s[i]-'a'];
	}
	e[id]=now;
}
queue<int> q;
void build(){
	for(int i=0;i<26;i++) if(tree[0][i]) q.push(tree[0][i]);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(tree[now][i]) {
				fail[tree[now][i]]=tree[fail[now]][i];
				q.push(tree[now][i]);
			}
			else tree[now][i]=tree[fail[now]][i];
		}
	}
}
int siz[N];

vector<int> G[N];
void dfs(int u){
	for(int v:G[u]){
		dfs(v);
		siz[u]+=siz[v];
	}
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		insert(s,i);
	}
	build();
	string s;
	cin>>s;
	int SIZE=s.size();
	int now=0;
	for(int i=0;i<SIZE;i++){
		now=tree[now][s[i]-'a'];
		siz[now]++;
	}
	for(int i=1;i<=cnt;i++)G[fail[i]].push_back(i);
	dfs(0);
	for(int i=1;i<=n;i++) cout<<siz[e[i]]<<"\n";

}