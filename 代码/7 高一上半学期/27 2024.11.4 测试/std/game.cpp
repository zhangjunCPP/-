#include<bits/stdc++.h>
using namespace std;
#define ln node<<1
#define rn node<<1|1
#define mid (l+r>>1)
typedef long long ll;
const int N=2e5+99;
int n,q,m,ptn,a[N];
struct tree{
	int f[33],g[33],tg;
	tree(){ tg=0; }
}tr[N*4];
void pushup(int node){
	for(int i=1;i<=m+1;i++)
		tr[node].f[i]=tr[ln].f[tr[rn].f[i]],tr[node].g[i]=tr[ln].g[tr[rn].g[i]];
	return;
}
void pushdown(int node){
	if(tr[node].tg){
		tr[ln].tg^=1; tr[rn].tg^=1; tr[node].tg^=1;
		swap(tr[ln].f,tr[ln].g); swap(tr[rn].f,tr[rn].g);
	}
	return;
}
void build(int node,int l,int r){
	if(l==r){
		for(int i=1;i<=m+1;i++)
			if(!a[l]){
				tr[node].f[i]=min(i+1,m+1);
				if(i!=m+1) tr[node].g[i]=min(i+1,m+1);
				else tr[node].g[i]=1;
			}
			else{
				if(i!=m+1) tr[node].f[i]=min(i+1,m+1);
				else tr[node].f[i]=1;
				tr[node].g[i]=min(i+1,m+1);
			}
		return;
	}
	build(ln,l,mid); build(rn,mid+1,r);
	pushup(node);
	return;
}
void change(int node,int l,int r,int tarl,int tarr){
	if(tarl<=l&&r<=tarr){
		tr[node].tg^=1;
		swap(tr[node].f,tr[node].g);
		return;
	}
	pushdown(node);
	if(tarl<=mid) change(ln,l,mid,tarl,tarr);
	if(tarr>mid) change(rn,mid+1,r,tarl,tarr);
	pushup(node);
	return;
}
void query(int node,int l,int r,int tarl,int tarr,int &ans){
	if(tarl<=l&&r<=tarr){
		ans=tr[node].f[ans];
		return;
	}
	pushdown(node);
	if(tarr>mid) query(rn,mid+1,r,tarl,tarr,ans);
	if(tarl<=mid) query(ln,l,mid,tarl,tarr,ans);
	pushup(node);
	return;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>q;
	ll tp,l,r,d,ans;
	for(int i=1;i<=n;i++){
		cin>>d;
		a[i]=d&1;
	}
	build(1,1,n);
	while(q--){
		cin>>tp>>l>>r;
		if(tp==1){
			cin>>d;
			d&=1;
			if(d) change(1,1,n,l,r);
		}
		else{
			int ans=m+1;
			query(1,1,n,l,r,ans);
			if(ans!=1)
				cout<<1<<'\n';
			else
				cout<<2<<'\n';
		}
	}
	return 0;
}