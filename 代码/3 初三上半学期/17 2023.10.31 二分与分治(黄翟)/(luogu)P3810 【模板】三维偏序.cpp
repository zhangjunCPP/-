#include<bits/stdc++.h>
using namespace std;
const int N=100100;
struct Node {
	int s,c,m,cnt,sum;
}a[N],tmp[N];
int n,k;
int tot;
int ans[N],tree[N*4];
int cmp(Node x, Node y) {
	if(x.s==y.s &&x.c==y.c)return x.m<y.m;
	if(x.s==y.s)return x.c<y.c;
	return x.s<y.s;
}
int cmp2(Node x, Node y) {
	if(x.c==y.c)return x.m<y.m;
	return x.c<y.c;
}
int lowbit(int x) {return x&(-x);}
void add(int x,int val) {for(int i=x;i<=k;i+=lowbit(i))tree[i]+=val;}
int ask(int x) {
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))ans+=tree[i];
	return ans;
}
void solve(int l,int r) {
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	sort(tmp+l,tmp+mid+1,cmp2);
	sort(tmp+mid+1,tmp+r+1,cmp2);
	int j=l;
	for(int i=mid+1;i<=r;i++){
		while(j<=mid&&tmp[j].c<=tmp[i].c){
			add(tmp[j].m,tmp[j].cnt);
			j++;
		}
		tmp[i].sum+=ask(tmp[i].m);
	}
	for(int i=l;i<j;i++)add(tmp[i].m,-tmp[i].cnt);
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i].s>>a[i].c>>a[i].m;
	sort(a+1,a+n+1,cmp);
	tmp[1]=a[1];
	tmp[1].cnt=1;
	tot=1;
	for(int i=2;i<=n;i++){
		if(tmp[tot].s==a[i].s&&tmp[tot].c==a[i].c&&tmp[tot].m==a[i].m)tmp[tot].cnt++;
		else tmp[++tot]=a[i],tmp[tot].cnt=1;
	}
	solve(1,tot);
	for(int i=1;i<=tot;i++)ans[tmp[i].sum+tmp[i].cnt-1]+=tmp[i].cnt;
	for(int i=0;i<n;i++)cout<<ans[i]<< "\n";
	return 0;
}