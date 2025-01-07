#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;
int n;
struct node{
	int x_1,y_1,x_2,y_2;
}a[N];
int tmp1[N],cnt_x,tmp2[N],cnt_y;
int tree1[N],tree2[N];
int lowbit(int x){return x&(-x);}
void add(int tree[],int x,int y){for(int i=x;i<=cnt_y;i+=lowbit(i))tree[i]+=y;}
int query(int tree[],int x){int ans=0;for(int i=x;i;i-=lowbit(i))ans+=tree[i];return ans;}
#define ls (k<<1)
#define rs (k<<1|1)
struct node2{
	int l,r;
	int sum;
}tree[N*4];
node2 update(const node2&x,const node2&y){return{x.l+y.l,x.r+y.r,x.sum+y.sum+x.r*y.l};}
void modify(int k,int l,int r,int x,int val){
	if(l==r){
		if(val==1)tree[k].l++;
		else if(val==2)tree[k].r++;
		else if(val==3)tree[k].l--;
		else if(val==4)tree[k].r--;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modify(ls,l,mid,x,val);
	else modify(rs,mid+1,r,x,val);
	tree[k]=update(tree[ls],tree[rs]);
}
node2 ask(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tree[k];
	int mid=(l+r)>>1;
	node2 ans={0,0,0};
	if(x<=mid)ans=update(ask(ls,l,mid,x,y),ans);
	if(y>mid)ans=update(ans,ask(rs,mid+1,r,x,y));
	return ans;
}
int d[N];	
vector<pair<int,int>>G[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x_1>>a[i].x_2>>a[i].y_1>>a[i].y_2;
		tmp1[++cnt_x]=a[i].x_1,tmp1[++cnt_x]=a[i].x_2;
		tmp2[++cnt_y]=a[i].y_1,tmp2[++cnt_y]=a[i].y_2;
	}
	sort(tmp1+1,tmp1+cnt_x+1);
	sort(tmp2+1,tmp2+cnt_y+1);
	cnt_x=unique(tmp1+1,tmp1+cnt_x+1)-tmp1-1;
	cnt_y=unique(tmp2+1,tmp2+cnt_y+1)-tmp2-1;
	for(int i=1;i<=n;i++){
		a[i].x_1=lower_bound(tmp1+1,tmp1+cnt_x+1,a[i].x_1)-tmp1;
		a[i].x_2=lower_bound(tmp1+1,tmp1+cnt_x+1,a[i].x_2)-tmp1;
		a[i].y_1=lower_bound(tmp2+1,tmp2+cnt_y+1,a[i].y_1)-tmp2;
		a[i].y_2=lower_bound(tmp2+1,tmp2+cnt_y+1,a[i].y_2)-tmp2;
	}
	for(int i=1;i<=n;i++){
		G[a[i].x_1].push_back({i,1});
		G[a[i].x_2].push_back({i,-1});
	}
	for(int i=1;i<=cnt_x;i++){
		for(auto it:G[i]){
			int j=it.first,opt=it.second;
			int L=a[j].y_1,R=a[j].y_2;
			if(opt==1)d[j]+=query(tree1,R)-query(tree2,L);
			add(tree1,L,opt),add(tree2,R,opt);
		}
	}
	for(int i=1;i<=cnt_x;i++){
		for(auto it:G[i]){			
			int j=it.first,opt=it.second;
			int L=a[j].y_1,R=a[j].y_2;
			if(opt==1)d[j]-=query(tree1,R)-query(tree2,L),add(tree1,L,opt),add(tree2,R,opt);
			else d[j]+=query(tree1,R)-query(tree2,L)-1;
		}
	}
	memset(tree1,0,sizeof tree1);
	memset(tree2,0,sizeof tree2);
	int sum=0;
	for(int i=1;i<=n;i++)sum+=d[i]*(n-2)-d[i]*(d[i]-1);
	int ans=n*(n-1)*(n-2)/6-sum/2;
	for(int i=1;i<=cnt_x;i++){
		for(auto it:G[i]){
			int j=it.first,opt=it.second;
			int L=a[j].y_1,R=a[j].y_2;
			if(opt==1){
				modify(1,1,cnt_y,L,1);
				modify(1,1,cnt_y,R,2);
				add(tree1,L,opt);
				add(tree2,R,opt);
			}
			else{
				int cnt=query(tree1,R)-query(tree2,L)-1;
				ans-=cnt*(cnt-1)/2-ask(1,1,cnt_y,L,R).sum;
				modify(1,1,cnt_y,L,3);
				modify(1,1,cnt_y,R,4);
				add(tree1,L,opt);
				add(tree2,R,opt);
			}
		}
	}
	cout<<ans;
	return 0;
}