#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n;
int a[N];
int tree[N*4];
void build(int k,int l,int r){
	if(l==r) {
		tree[k]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=max(tree[k<<1],tree[k<<1|1]);
}
int query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r) return tree[k];
	int mid=(l+r)>>1;
	int ans=-1;
	if(x<=mid) ans=max(ans,query(k<<1,l,mid,x,y));
	if(y>mid) ans=max(ans,query(k<<1|1,mid+1,r,x,y));
	return ans;	
}
bool vis[N];
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	} 
	return x;
}
int main(){
	freopen("mexmax.in","r",stdin);
	freopen("mexmax.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	int q;
	q=read();
	while(q--){
		int k;
		k=read();
		for(int i=0;i<=n;i++) vis[i]=false;
		for(int l=1;l+k-1<=n;l++) {
			int r=l+k-1;
			int Max=query(1,1,n,l,r);
			vis[Max]=true;
		}
		int ans=0;
		while(vis[ans]) ans++;
		cout<<ans<<"\n";
	}
	return 0;
}
