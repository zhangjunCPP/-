#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
int n,m;
int tree[N];
int lowbit(int x) {return x&(-x);}
void update(int x,int y){for(int i=x;i<=m*2;i+=lowbit(i))  tree[i]+=y;}
int ask(int x){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i)) ans+=tree[i];
	return ans;
}
struct node2{
	int need;
	int first;
	int id;
}q[N];
int v[N],nex[N];
int cnt;
void add(int s,int t){
	v[++cnt]=t;
	nex[cnt]=q[s].first;
	q[s].first=cnt;
}
int L[N],R[N],val[N];
int ans[N];
node2 tmp1[N],tmp2[N];
void solve(int l,int r,int x,int y){
	if(l==r) {
		for(int i=x;i<=y;i++) ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1;
	for(int i=l;i<=mid;i++) update(L[i],val[i]),update(R[i]+1,-val[i]);
	int cnt1=0,cnt2=0;
	for(int i=x;i<=y;i++) {
		int tmp=0;
		for(int j=q[i].first;j&&tmp<=q[i].need;j=nex[j]){
			tmp+=ask(v[j])+ask(v[j]+m);
		}
		if(tmp>=q[i].need) tmp1[++cnt1]=q[i];
		else q[i].need-=tmp,tmp2[++cnt2]=q[i];
	}
	int now=x-1;
	for(int i=1;i<=cnt1;i++) q[++now]=tmp1[i];
	for(int i=1;i<=cnt2;i++) q[++now]=tmp2[i];
	for(int i=l;i<=mid;i++) update(L[i],-val[i]),update(R[i]+1,val[i]);
	solve(l,mid,x,x+cnt1-1);
	solve(mid+1,r,x+cnt1,y);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		add(x,i);	
	}
	for(int i=1;i<=n;i++){
		cin>>q[i].need;
		q[i].id=i;	
	}
	int k;
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>L[i]>>R[i]>>val[i];
		if(R[i]<L[i]) R[i]+=m;
	}
	solve(1,k+1,1,n);
	for(int i=1;i<=n;i++ ) {
		if(ans[i]==k+1) cout<<"NIE\n";
		else cout<<ans[i]<<"\n";
	}
	return 0;
}
