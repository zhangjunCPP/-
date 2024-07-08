#include <bits/stdc++.h>
using namespace std;
const int N=5e6+10,INF=1e9;
int n,m;
int lowbit(int x){return x&-x;}
int a[N],b[N];
int la[N],cnt_la,ra[N],cnt_ra;
int lb[N],cnt_lb,rb[N],cnt_rb;
int suma[N],sumb[N];
void clear() {
	cnt_la=cnt_ra=cnt_lb=cnt_rb=0;
}
struct node {
	int tree[N];
	void add(int x,int y) {for(int i=x;i<=2*(n+m);i+=lowbit(i))tree[i]=max(tree[i],y);}
	int query(int x) {
		int ans=-INF;
		for(int i=x;i;i-=lowbit(i))ans=max(ans,tree[i]);
		return ans;
	}
}tree1,tree2;
void solve() {
	clear();
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<=n;i++)if(a[i]==1)la[++cnt_la]=i;
	for(int i=1;i<=m;i++)if(b[i]==1)lb[++cnt_lb]=i;
	for(int i=n;i>=1;i--)if(a[i]==3)ra[++cnt_ra]=i;
	for(int i=m;i>=1;i--)if(b[i]==3)rb[++cnt_rb]=i;
	for(int i=1;i<=n;i++)suma[i]=suma[i-1]+(a[i]==2);
	for(int i=1;i<=m;i++)sumb[i]=sumb[i-1]+(b[i]==2);

	la[0]=0,lb[0]=0;
	ra[0]=n+1,rb[0]=m+1;
	suma[n+1]=suma[n],sumb[m+1]=sumb[m];
	
	for(int i=0;i<=2*(n+m);i++)tree1.tree[i]=tree2.tree[i]=-INF;
	int ans=0;
	int i=-1;
	for(int j=min(cnt_ra,cnt_rb);j>=0;j--) {
		while(i<min(cnt_la,cnt_lb)&&la[i+1]<ra[j]&&lb[i+1]<rb[j]) {
			i++;
			tree1.add(sumb[lb[i]]-suma[la[i]]+n+m,i-suma[la[i]]);
			tree2.add(suma[la[i]]-sumb[lb[i]]+n+m,i-sumb[lb[i]]);
		}
		int tmp=sumb[rb[j]]-suma[ra[j]];
		ans=max({ans,tree1.query(tmp+n+m)+j+suma[ra[j]],tree2.query(-tmp+n+m)+j+sumb[rb[j]]});
	}
	cout<<ans<<"\n";

}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}