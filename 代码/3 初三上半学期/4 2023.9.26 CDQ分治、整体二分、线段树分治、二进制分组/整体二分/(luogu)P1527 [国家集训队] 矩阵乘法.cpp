#include<bits/stdc++.h>
using namespace std;
const int N=6e6+10;
int n,t;
struct node{
	int x,y,val;
}point[N];
int cnt;
bool cmp(node &a,node &b){
	return a.val<b.val;
}
struct node2{
	int x1,y1,x2,y2,k;
}q[N];
int id[N];
int tree[510][510];
int lowbit(int x){return x&(-x);}
void add(int x,int y,int val){for(int i=x;i<=n;i+=lowbit(i))for(int j=y;j<=n;j+=lowbit(j))tree[i][j]+=val;}
int query(int x,int y){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))for(int j=y;j>0;j-=lowbit(j)) ans+=tree[i][j];
	return ans;
}
int ask(int x1,int y1,int x2,int y2){
	return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
}
int ans[N];
int cur[N];
int tmp1[N],tmp2[N];
void solve(int l,int r,int x,int y){
	if(x>y) return;
	if(l==r){
		for(int i=x;i<=y;i++) ans[id[i]]=point[l].val;
		return;
	}
	int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++) add(point[i].x,point[i].y,1); 
	int cnt1=0,cnt2=0;
	for(int i=x;i<=y;i++){
		int now=id[i];
		int sum=cur[now]+ask(q[now].x1,q[now].y1,q[now].x2,q[now].y2);
		if(sum>=q[now].k) tmp1[++cnt1]=now;
		else tmp2[++cnt2]=now,cur[now]=sum;	
	}
	int now=x-1;
	for(int i=1;i<=cnt1;i++) id[++now]=tmp1[i];
	for(int i=1;i<=cnt2;i++) id[++now]=tmp2[i];
	for(int i=l;i<=mid;i++) add(point[i].x,point[i].y,-1);
	solve(l,mid,x,x+cnt1-1);
	solve(mid+1,r,x+cnt1,y);
}
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){for(int j=1;j<=n;j++){int x;cin>>x;point[++cnt]={i,j,x};}} 
	sort(point+1,point+cnt+1,cmp);
	for(int i=1;i<=t;i++ ){
		cin>>q[i].x1>>q[i].y1>>q[i].x2>>q[i].y2>>q[i].k;
		id[i]=i;
	}
	solve(1,cnt,1,t);
	for(int i=1;i<=t;i++) cout<<ans[i]<<"\n";
	return 0;
}
