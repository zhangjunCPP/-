#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N],tmp[N];
struct node{
	int l,r,id;
}q[N];
ll sum[N],num[N];
ll ans[N];
ll val1,val2;
int L=1,R=0;
void add(int x){
	val1+=sum[num[x]+1]+1;
	val2++;
	num[x]++;
	sum[num[x]]++;
	// cout<<"L="<<L<<" R="<<R<<":\nnum:";
	// for(int i=1;i<=5;i++)cout<<num[i]<<" ";
	// cout<<"\nsum:";
	// for(int i=1;i<=5;i++)cout<<sum[i]<<" ";
	// cout<<"\n";
}
void del(int x){
	val1-=sum[num[x]];
	val2--;
	sum[num[x]]--;
	num[x]--;
}
int main(){
	freopen("hoshino.in","r",stdin);
	freopen("hoshino.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>n>>m;
	int block=500;
	block++;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	int tot=n;
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(tmp+1,tmp+tot+1,a[i])-tmp;
	for(int i=1;i<=m;i++){cin>>q[i].l>>q[i].r;q[i].id=i;}
	sort(q+1,q+m+1,[&](const node&x,const node&y){
		if(x.l/block!=y.l/block)return x.l<y.l;
		return (x.l/block)&1?x.r>y.r:x.r<y.r;
	});
	for(int i=1;i<=m;i++){
		while(L>q[i].l)add(a[--L]);
		while(R<q[i].r)add(a[++R]);
		while(L<q[i].l)del(a[L++]);
		while(R>q[i].r)del(a[R--]);
		ans[q[i].id]=val1-val2;
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}
/*
1
8 10
2 5 3 1 5 2 1 3
1 4
6 8
3 7
4 6
1 7
4 8
6 6
4 7
7 8
5 8
*/
/*
1
5 1
3 1 5 2 1
1 5
*/