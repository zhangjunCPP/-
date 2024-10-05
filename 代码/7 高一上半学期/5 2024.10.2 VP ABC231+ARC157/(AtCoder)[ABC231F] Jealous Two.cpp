#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n;
struct node{
	int val_a,val_b;
}a[N];
bool cmp(const node&x,const node&y){
	if(x.val_a!=y.val_a)return x.val_a>y.val_a;
	return x.val_b>y.val_b;
}
int tree[N];
int lowbit(int x){return x&(-x);}
void add(int x,int val){
	for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;
}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
int tmp_a[N],tmp_b[N];
int sum[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].val_a;
	for(int i=1;i<=n;i++)cin>>a[i].val_b;

	for(int i=1;i<=n;i++)tmp_a[i]=a[i].val_a,tmp_b[i]=a[i].val_b;
	sort(tmp_a+1,tmp_a+n+1);
	sort(tmp_b+1,tmp_b+n+1);
	int len_a=unique(tmp_a+1,tmp_a+n+1)-tmp_a-1;
	int len_b=unique(tmp_b+1,tmp_b+n+1)-tmp_b-1;

	for(int i=1;i<=n;i++){
		a[i].val_a=lower_bound(tmp_a+1,tmp_a+len_a+1,a[i].val_a)-tmp_a;
		a[i].val_b=lower_bound(tmp_b+1,tmp_b+len_b+1,a[i].val_b)-tmp_b;
	}
	sort(a+1,a+n+1,cmp);
	// for(int i=1;i<=n;i++)cout<<a[i].val_a<<" "<<a[i].val_b<<"\n";
	int ans=0;
	for(int i=1;i<=n;i++){
		add(a[i].val_b,1);
		ans+=query(a[i].val_b);
	}
	for(int i=1;i<=n;i++)sum[a[i].val_a]++;
	for(int i=1;i<=n;i++)ans+=sum[i]*(sum[i]-1)/2;
	cout<<ans;
}