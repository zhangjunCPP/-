#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m;
int block,tot;
int l[N],r[N],belong[N];
struct node{
	int l,r,id;
}q[N];
bool cmp(const node&x,const node&y){
	if(belong[x.l]==belong[y.l])return x.r<y.r;
	else return belong[x.l]<belong[y.l];
}
int ans[N];
int a[N],tmp[N];
void init(){
	cin>>n>>m;
	block=sqrt(n);
	tot=n/block;
	for(int i=1;i<=tot;i++)l[i]=r[i-1]+1,r[i]=i*block;
	if(n%block)l[tot+1]=r[tot]+1,r[tot+1]=n,tot++;
	for(int i=1;i<=tot;i++)for(int j=l[i];j<=r[i];j++)belong[j]=i;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	int num=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+num+1,a[i])-tmp;
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+m+1,cmp);
}
int sum[N];
void solve(){
	int lastblock=0;
	int L=0,R=0;
	int lastans=0;
	for(int i=1;i<=m;i++){
		if(belong[q[i].l]==belong[q[i].r]){
			for(int j=q[i].l;j<=q[i].r;j++)sum[a[j]]=0;
			for(int j=q[i].l;j<=q[i].r;j++)sum[a[j]]++;
			for(int j=q[i].l;j<=q[i].r;j++){
				ans[q[i].id]=max(ans[q[i].id],sum[a[j]]*tmp[a[j]]);
				sum[a[j]]=0;
			}
			continue;
		}
		int nowblock=belong[q[i].l];
		if(nowblock!=lastblock){
			for(int j=L;j<=R;j++)sum[a[j]]=0;
			L=r[nowblock];
			R=L-1;
			lastans=0;
			lastblock=nowblock;
		}
		while(R<q[i].r){
			++R;
			sum[a[R]]++;
			lastans=max(lastans,sum[a[R]]*tmp[a[R]]);
		}
		int p=L,tmpans=lastans;
		while(p>q[i].l){
			--p;
			sum[a[p]]++;
			tmpans=max(tmpans,sum[a[p]]*tmp[a[p]]);
		}
		while(p<L)sum[a[p]]--,p++;
		ans[q[i].id]=max(tmpans,lastans);

	}
}
signed main(){
	init();
	solve();
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}