#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,m;
int block;
int l[N],r[N];
int belong[N];
inline int lowbit(int x){return x&-x;}
int tree[N];
inline void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
inline int query(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i))sum+=tree[i];
	return sum;
}
int a[N],tmp[N];
struct node{
	int l,r,id;
	bool operator<(const node&oth)const{
		if(belong[l]!=belong[oth.l])return l<oth.l;
		return (belong[l]&1)?r<oth.r:r>oth.r;
	}
}q[N];
struct node2{
	int l,r,id,opt;
};
vector<node2>vl[N],vr[N];
ll ans[N];
void init_block(int n){
	block=sqrt(n);
	int tot=n/block;
	for(int i=1;i<=n;i++)l[i]=r[i-1]+1,r[i]=i*block;
	if(n%block)l[tot+1]=r[tot]+1,r[tot+1]=n,tot++;
	for(int i=1;i<=tot;i++)for(int j=l[i];j<=r[i];j++)belong[j]=i;
	belong[0]=1;
}
ll suml[N],sumr[N];
ll cnt1[N],cnt2[N];
inline void addl(int x){
	for(int i=x;i>=l[belong[x]];i--)cnt1[i]++;
	for(int i=belong[x]-1;i;i--)cnt2[i]++;
}
int tot;
inline void addr(int x){
	for(int i=x;i<=r[belong[x]];i++)cnt1[i]++;
	for(int i=belong[x]+1;i<=belong[tot];i++)cnt2[i]++;
}
inline int solve(int x){return cnt1[x]+cnt2[belong[x]];}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	init_block(n+10);
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	tot=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;
	for(int i=1;i<=n;i++){
		suml[i]=suml[i-1]+query(n)-query(a[i]);
		add(a[i],1);
	}
	memset(tree,0,sizeof tree);
	for(int i=n;i;i--){
		sumr[i]=sumr[i+1]+query(a[i]-1);
		add(a[i],1);
	}
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+m+1);
	int L=1,R=0;
	for(int i=1;i<=m;i++){
		int LL=q[i].l,RR=q[i].r,id=q[i].id;
		if(R<RR)vl[L-1].push_back({R+1,RR,id,0}),ans[id]+=suml[RR]-suml[R];
		if(R>RR)vl[L-1].push_back({RR+1,R,id,1}),ans[id]-=suml[R]-suml[RR];
		if(L>LL)vr[RR+1].push_back({LL,L-1,id,0}),ans[id]+=sumr[LL]-sumr[L];
		if(L<LL)vr[RR+1].push_back({L,LL-1,id,1}),ans[id]-=sumr[L]-sumr[LL];
		L=LL,R=RR;
	}
	for(int i=1;i<=n;i++){
		addl(a[i]-1);
		for(auto it:vl[i]){
			int sum=0;
			for(int j=it.l;j<=it.r;j++)sum+=solve(a[j]);
			if(it.opt)ans[it.id]+=sum;
			else ans[it.id]-=sum;
		}
	}
	memset(cnt1,0,sizeof cnt1);
	memset(cnt2,0,sizeof cnt2);
	for(int i=n;i;i--){
		addr(a[i]+1);
		for(auto it:vr[i]){
			int sum=0;
			for(int j=it.l;j<=it.r;j++)sum+=solve(a[j]);
			if(it.opt)ans[it.id]+=sum;
			else ans[it.id]-=sum;
		}
	}
	for(int i=1;i<=m;i++)ans[q[i].id]+=ans[q[i-1].id];
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}