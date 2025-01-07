#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1010;
struct node{
	int v,nex;
}a[N];
int first[N],cnt=1;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dfn[N],low[N],tot;
bool cut[N];
stack<int>s;
int col;
vector<int> ans[N];
int rt;
void Tarjan(int u,int edge){
	dfn[u]=low[u]=++tot;
	s.push(u);
	int sum=0;
	for(int i=first[u];i;i=a[i].nex){
		sum++;
		int v=a[i].v;
		if(!dfn[v]){
			Tarjan(v,i);
			low[u]=min(low[u],low[v]);
			if((u==rt&&sum>1)||(u!=rt&&low[v]>=dfn[u]))cut[u]=true;
			if(low[v]>=dfn[u]){
				++col;
				ans[col].push_back(u);
				while(s.top()!=v){
					ans[col].push_back(s.top());
					s.pop();
				}
				ans[col].push_back(v);
				s.pop();
			}
		}
		else if(i!=(edge^1))low[u]=min(low[u],dfn[v]);
	}
}
int u[N],v[N];
void init(){
	cnt=1,tot=col=0;
	memset(first,0,sizeof first);
	memset(low,0,sizeof low);
	memset(dfn,0,sizeof dfn);
	memset(cut,0,sizeof cut);
	for(int i=0;i<N;i++)ans[i].clear();
}
signed main(){
	int Case=0;
	int n,m;
	cin>>m;
	while(true){
		init();
		Case++;
		n=0;
		if(m==0)return 0;
		for(int i=1;i<=m;i++){
			cin>>u[i]>>v[i];
			n=max({n,u[i],v[i]});
			add(u[i],v[i]);
			add(v[i],u[i]);
		}
		for(int i=1;i<=n;i++)if(!dfn[i])rt=i,Tarjan(i,0);
		if(col==1)printf("Case %lld: 2 %lld\n",Case,n*(n-1)/2);
		else{
			int ans1=0,ans2=1;
			for(int i=1;i<=col;i++){
				int sum=0;
				for(int j:ans[i])if(cut[j])sum++;
				if(sum==1)ans1++,ans2*=ans[i].size()-1;
			}
			printf("Case %lld: %lld %lld\n",Case,ans1,ans2);
		}
		cin>>m;
	}
}