#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{int u,v,l,r;}a[N];
bool cmp(const node&x,const node&y){return x.r>y.r;}
int fa[N];
int find(int x){
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fx]=fy;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;++i)cin>>a[i].u>>a[i].v>>a[i].l>>a[i].r;
	sort(a+1,a+m+1,cmp);
	int ans=0;
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i)fa[i]=i;
		for(int i=1;i<=m;++i)
			if(a[i].l<=a[j].l){
				merge(a[i].u,a[i].v);
				if(find(1)==find(n)){ans=max(ans,a[i].r-a[j].l+1);break;}
			}
	}
	if(ans)cout<<ans;
	else puts("Nice work, Dima!");
	return 0;
}