#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m;
int block;
int l[N],r[N],belong[N];
void init_block(){
	block=sqrt(n);
	int tot=n/block;
	for(int i=1;i<=tot;i++)l[i]=r[i-1]+1,r[i]=i*block;
	if(n%block)l[tot+1]=r[tot]+1,r[tot+1]=n,tot++;
	for(int i=1;i<=tot;i++)for(int j=l[i];j<=r[i];j++)belong[j]=i;
}
int a[N],b[N];
int pre[N],nex[N];
struct node{
	int l,r,u,v,id;
	bool operator<(const node&oth)const{
		if(belong[u]==belong[oth.u])return v<oth.v;
		return u<oth.u;
	}
}q[N];
int ans[N];
struct node2{
	int x,val,opt;
}sta[N*10];
int top;
int mx[N];
inline void add(int x){
	sta[++top]={x,pre[x],0};
	pre[x]=(x==l[belong[x]]?x:pre[x-1]);
	sta[++top]={x,nex[x],1};
	nex[x]=(x==r[belong[x]]?x:nex[x+1]);
	if(x!=l[belong[x]]&&pre[x]!=x)sta[++top]={pre[x],nex[pre[x]],1},nex[pre[x]]=nex[x];
	if(x!=r[belong[x]]&&nex[x]!=x)sta[++top]={nex[x],pre[nex[x]],0},pre[nex[x]]=pre[x];
	sta[++top]={belong[x],mx[belong[x]],2};
	mx[belong[x]]+=(x-pre[x]+1)*(nex[x]-x+1);
}
inline void del(){
	if(sta[top].opt==0)pre[sta[top].x]=sta[top].val;
	if(sta[top].opt==1)nex[sta[top].x]=sta[top].val;
	if(sta[top].opt==2)mx[sta[top].x]=sta[top].val;
	top--;
}
inline int solve(int L,int R){
	int last=-1;
	int sum=0;
	for(int i=L;i<=R;i++){
		if(pre[i]!=i+1){
			if(last==-1)last=i;
			if(pre[i+1]==i+2||i==R)sum+=(i-last+1)*(i-last+2)/2;
		}
		else last=-1;
	}
	return sum;
}
inline int ask(int L,int R){
	if(belong[L]==belong[R])return solve(L,R);
	int ans=solve(L,r[belong[L]])+solve(l[belong[R]],R);
	int last=max(L,pre[r[belong[L]]]);
	for(int i=belong[L]+1;i<=belong[R]-1;i++){
		ans+=mx[i]+(r[i-1]-last+1)*(nex[l[i]]-l[i]+1);
		if(pre[r[i]]!=l[i])last=pre[r[i]];
	}
	ans+=(min(R,nex[l[belong[R]]])-l[belong[R]]+1)*(r[belong[R]-1]-last+1);
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	init_block();
	for(int i=1;i<=n;i++)cin>>a[i],b[a[i]]=i;
	for(int i=1;i<=n;i++)pre[i]=i+1,nex[i]=i-1;
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r>>q[i].u>>q[i].v,q[i].id=i;
	sort(q+1,q+m+1);
	int L=1,R=0;
	int lastblock=-1;
	for(int i=1;i<=m;i++){
		if(belong[q[i].u]==belong[q[i].v]){
			while(top)del();
			for(int j=q[i].u;j<=q[i].v;j++)add(b[j]);
			ans[q[i].id]=ask(q[i].l,q[i].r);
			while(top)del();
			continue;
		}
		if(belong[q[i].u]!=lastblock){
			while(top)del();
			L=r[belong[q[i].u]]+1,R=L-1;
			lastblock=belong[q[i].u];
		}
		while(R<q[i].v)add(b[++R]);
		int last=top;
		for(int j=L-1;j>=q[i].u;j--)add(b[j]);
		ans[q[i].id]=ask(q[i].l,q[i].r);
		while(top>last)del();
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}