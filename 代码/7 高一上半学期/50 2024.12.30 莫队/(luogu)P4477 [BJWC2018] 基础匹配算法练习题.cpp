#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,z;
int block;
int l[N],r[N],belong[N];
void init_block(){
	block=sqrt(m);
	int tot=m/block;
	for(int i=1;i<=tot;i++)l[i]=r[i-1]+1,r[i]=i*block;
	if(m%block)l[tot+1]=r[tot]+1,r[tot+1]=m,tot++;
	for(int i=1;i<=tot;i++)for(int j=l[i];j<=r[i];j++)belong[j]=i;
}
struct node{
	int l,r,id;
	bool operator<(const node&oth)const{
		if(belong[l]==belong[oth.l])return r<oth.r;
		return l<oth.l;
	}
}q[N];
struct node2{
	int x,val,opt;
}sta[N];
int top;
int fa[N];
int Min[N],siz[N];
int find(int x){while(x!=fa[x])x=fa[x];return x;}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	if(siz[fx]>siz[fy])swap(fx,fy);
	sta[++top]={fx,fa[fx],0},fa[fx]=fy;
	sta[++top]={fy,siz[fy],1},siz[fy]+=siz[fx];
	sta[++top]={fy,Min[fy],2},Min[fy]=min(Min[fy],Min[fx]);
}
void del(){
	if(sta[top].opt==0)fa[sta[top].x]=sta[top].val;
	if(sta[top].opt==1)siz[sta[top].x]=sta[top].val;
	if(sta[top].opt==2)Min[sta[top].x]=sta[top].val;
	top--;
}
int a[N],b[N],tmp[N];
int ans[N];
int sum;
void add(int x){
	int val=Min[find(x)];
	if(val)sum++,merge(val-1,val);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>z;
	init_block();
	for(int i=0;i<=n;i++)fa[i]=Min[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++)cin>>a[i],tmp[i]=a[i];
	sort(tmp+1,tmp+n+1);
	for(int i=1;i<=m;i++)cin>>b[i],a[i]=upper_bound(tmp+1,tmp+n+1,z-b[i])-tmp-1;	
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+T+1);
	int L=1,R=0;
	int lastblock=-1;
	for(int i=1;i<=T;i++){
		if(belong[q[i].l]==belong[q[i].r]){
			sum=0;while(top)del();
			for(int j=q[i].l;j<=q[i].r;j++)add(a[j]);
			ans[q[i].id]=sum;
			sum=0;while(top)del();
			continue;
		}
		if(belong[q[i].l]!=lastblock){
			sum=0;while(top)del();
			L=r[belong[q[i].l]]+1,R=L-1;
			lastblock=belong[q[i].l];
		}
		while(R<q[i].r)add(a[++R]);
		int last=top,lastsum=sum;
		for(int j=L-1;j>=q[i].l;j--)add(a[j]);
		ans[q[i].id]=sum;
		sum=lastsum;
		while(top>last)del();
	}
	for(int i=1;i<=T;i++)cout<<ans[i]<<"\n";
}