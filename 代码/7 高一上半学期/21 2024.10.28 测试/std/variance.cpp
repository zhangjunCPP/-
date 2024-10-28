#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
class segment_tree
{
	struct segment
	{
		int l,r,maxn,lazy;
	}a[2000005];
	int arr[500005];
	public:
		void update(int pos)
		{
			a[pos].maxn=max(a[2*pos].maxn,a[2*pos+1].maxn);
		}
		void build(int pos,int l,int r)
		{
			a[pos]={l,r,0,0};
			if(l==r)
			{
				a[pos].maxn=arr[l];
				return;
			}
			int mid=l+r>>1;
			build(2*pos,l,mid);
			build(2*pos+1,mid+1,r);
			update(pos);
		}
		void set(int *start,int n)
		{
			for(int i=1;i<=n;i++)
				arr[i]=start[i];
			build(1,1,n);
		}
		void putlazy(int pos,int x)
		{
			a[pos].maxn+=x;
			a[pos].lazy+=x;
		}
		void pushdown(int pos)
		{
			putlazy(2*pos,a[pos].lazy);
			putlazy(2*pos+1,a[pos].lazy);
			a[pos].lazy=0;
		}
		void add(int pos,int l,int r,int x)
		{
			if(r<a[pos].l||l>a[pos].r||l>r)
				return;
			if(l<=a[pos].l&&a[pos].r<=r)
			{
				putlazy(pos,x);
				return;
			}
			pushdown(pos);
			add(2*pos,l,r,x);
			add(2*pos+1,l,r,x);
			update(pos);
		}
		int query(int pos,int l,int r)
		{
			if(r<a[pos].l||l>a[pos].r||l>r)
				return -inf;
			if(l<=a[pos].l&&a[pos].r<=r)
				return a[pos].maxn;
			pushdown(pos);
			return max(query(2*pos,l,r),query(2*pos+1,l,r));
		}
};
segment_tree t2,t3;
int a[500005],a2[500005],a3[500005];
int n,q;
signed main()
{


	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		a2[i]=a[i]+a[i+1];
	for(int i=1;i<=n;i++)
		a3[i]=a[i]+a[i+1]+a[i+2];
	t2.set(a2,n);
	t3.set(a3,n);
	for(int i=1;i<=q;i++)
	{
		int opt;
		cin>>opt;
		if(opt==1)
		{
			int l,r,x;
			cin>>l>>r>>x;
			if(l!=r)
			{
				t2.add(1,l-1,r,x);
				t2.add(1,l,r-1,x);
				t3.add(1,l-2,r,x);
				t3.add(1,l-1,r-1,x);
				t3.add(1,l,r-2,x);
			}
			else
			{
				t2.add(1,l-1,r,x);
				t3.add(1,l-2,r,x);
			}
		}
		else
		{
			int l,r;
			cin>>l>>r;
			int max2=t2.query(1,l,r-1);
			int max3=t3.query(1,l,r-2);
//			cout<<max2<<" "<<max3<<"\n";
			int ans1,ans2;
			if(max2*3<max3*2)
				ans1=max3,ans2=3;
			else
				ans1=max2,ans2=2;
			int d=abs(__gcd(ans1,ans2));
			ans1/=d;
			ans2/=d;
			cout<<1<<" "<<ans1<<" "<<ans2<<"\n";
		}
	}
}