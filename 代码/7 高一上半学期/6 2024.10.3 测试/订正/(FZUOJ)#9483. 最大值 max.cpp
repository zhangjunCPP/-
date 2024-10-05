#include<bits/stdc++.h>	
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int x,y,z,id;
}a[N];
struct node2{
	int n;
	int tree[N];
	int lowbit(int x){return x&-x;}
	void clear(int x){n=x;for(int i=1;i<=n;i++)tree[i]=0;}
	void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
	int query(int x){int ans=0;for(int i=x;i;i-=lowbit(i))ans+=tree[i];return ans;}
}tree;
int cnt[4][N];
bool cmp1(const node&x,const node&y){return x.x<y.x;}
bool cmp2(const node&x,const node&y){return x.y<y.y;}
void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2);sort(a+mid+1,a+r+1,cmp2);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&a[j].y<=a[i].y)tree.add(a[j].z,1),j++;
		cnt[0][a[i].id]+=tree.query(a[i].z);
	}
	for(int i=l;i<j;i++)tree.add(a[i].z,-1);
}
int C2(int n){return n*(n-1)/2;}
int C3(int n){return n*(n-1)*(n-2)/6;}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
		a[i].id=i;
	}
	tree.clear(n);
	memset(cnt,0,sizeof cnt);
	//一次三维偏序
	//abc
	sort(a+1,a+n+1,cmp1);
	cdq(1,n);
	//三次二维偏序
	//ab
	tree.clear(n);
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)cnt[1][a[i].id]=tree.query(a[i].y),tree.add(a[i].y,1);
	//ac
	tree.clear(n);
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++)cnt[2][a[i].id]=tree.query(a[i].z),tree.add(a[i].z,1);
	//bc
	tree.clear(n);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++)cnt[3][a[i].id]=tree.query(a[i].z),tree.add(a[i].z,1);
	int ans=n+C2(n)+C3(n);
	for(int i=1;i<=n;i++)ans=ans-cnt[0][i]-C2(cnt[1][i])-C2(cnt[2][i])-C2(cnt[3][i])+2*C2(cnt[0][i]);
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}