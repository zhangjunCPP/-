#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200+10;
int n,m;
struct node {
	int u,v,a,b,w;
}edge[N*N];
bool cmp(const node&x,const node&y) {
	if(x.w==y.w)return x.a<y.a;
	return x.w<y.w;
}
int fa[N];
int find(int x) {
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
pair<int,int> kruskal() {
	for(int i=1;i<=n;i++)fa[i]=i;
	sort(edge+1,edge+m+1,cmp);
	int cnt=0;
	int ans1=0,ans2=0;
	for(int i=1;i<=m;i++) {
		int fx=find(edge[i].u),fy=find(edge[i].v);
		if(fx!=fy) {
			fa[fx]=fy;
			ans1+=edge[i].a,ans2+=edge[i].b;
			cnt++;
		}
		if(cnt==n-1)break;
	}
	return {ans1,ans2};
}
void update(pair<int,int>&x,pair<int,int>y) {
	int val1=x.first*x.second,val2=y.first*y.second;
	if(val1>val2||(val1==val2&&x.first>y.first))x=y;
}
int check(int x_1,int y_1,int x_2,int y_2){return x_1*y_2-y_1*x_2;}
pair<int,int>ans={1e9,1e9};
void solve(pair<int,int>A,pair<int,int>B) {
	for(int i=1;i<=m;i++)edge[i].w=(A.second-B.second)*edge[i].a+(B.first-A.first)*edge[i].b;
	auto C=kruskal();
	update(ans,C);
	if(check(B.first-A.first,B.second-A.second,C.first-A.first,C.second-A.second)>=0)return;
	solve(A,C);
	solve(C,B);
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		cin>>edge[i].u>>edge[i].v>>edge[i].a>>edge[i].b;
		edge[i].u++,edge[i].v++;
	}
	for(int i=1;i<=m;i++)edge[i].w=edge[i].a;
	auto A=kruskal();
	update(ans,A);
	for(int i=1;i<=m;i++)edge[i].w=edge[i].b;
	auto B=kruskal();
	update(ans,B);
	solve(A,B);
	cout<<ans.first<<" "<<ans.second;
}