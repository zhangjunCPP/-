#include <bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
struct node2{
	int ls,rs;
	int id,sum;
}tree[N*50];
int tot;
void pushup(int k){tree[k].sum=tree[tree[k].ls].sum+tree[tree[k].rs].sum;}
void update(int &k,int l,int r,int x,int val){
	if(!k)k=++tot;
	if(l==r){
		tree[k].id=val;
		tree[k].sum++;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(tree[k].ls,l,mid,x,val);
	else update(tree[k].rs,mid+1,r,x,val);
	pushup(k);
}
void modify(int &x,int y){
	if(!x||!y){x|=y;return;}
	modify(tree[x].ls,tree[y].ls);
	modify(tree[x].rs,tree[y].rs);
	pushup(x);
}
int query(int k,int l,int r,int x){
	if(l==r)return tree[k].id;
	if(tree[k].sum<x)return -1;
	int mid=(l+r)>>1;
	int tmp=tree[tree[k].ls].sum;
	if(x<=tmp)return query(tree[k].ls,l,mid,x);
	else return query(tree[k].rs,mid+1,r,x-tmp);
}
int rt[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		update(rt[i],1,n,x,i);
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		int fx=find(u),fy=find(v);
		if(fx==fy)continue;
		fa[fy]=fx;
		modify(rt[fx],rt[fy]);
	}
	int q;
	cin>>q;
	while(q--){
		string op;
		int x,y;
		cin>>op>>x>>y;
		if(op=="Q")x=find(x),cout<<query(rt[x],1,n,y)<<"\n";
		else{
			int fx=find(x),fy=find(y);
			if(fx==fy)continue;
			fa[fy]=fx;
			modify(rt[fx],rt[fy]);
		}
	}

}