#include<bits/stdc++.h>
#define lson k<<1
#define rson k<<1|1
using namespace std;
const int N=1e7+10;
double a[N];
double Max[N];
int len[N];
int pushup(int k,int l,int r,double val){
	if(Max[k]<=val) return 0;
	if(l==r) return Max[k]>val;
	int mid=(l+r)>>1;
	if(Max[lson]<=val) return pushup(rson,mid+1,r,val);
	return pushup(lson,l,mid,val)+len[k]-len[lson];
}
void update(int k,int l,int r,int x,double val){
	if(l==r){
		Max[k]=val;
		len[k]=1;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(lson,l,mid,x,val);
	else if(x>mid) update(rson,mid+1,r,x,val);
	Max[k]=max(Max[lson],Max[rson]);
	len[k]=len[lson]+pushup(rson,mid+1,r,Max[lson]);
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++) {
		int x,y;
		cin>>x>>y;
		a[x]=y*1.0/x;
		update(1,1,n,x,a[x]);
		cout<<len[1]<<"\n";
	}
}