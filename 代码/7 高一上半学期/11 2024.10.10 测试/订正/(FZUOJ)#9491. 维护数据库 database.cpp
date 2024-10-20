#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int now;
int ch[N][2],tot=1;
int dep[N];
int tim[N];
void update(int x);
int merge(int x,int y);
void insert(int x){
	int p=1;
	for(int i=30;i>=0;i--){
		update(p);
		int tmp=(x>>i)&1;
		if(!ch[p][tmp])ch[p][tmp]=++tot,dep[tot]=dep[p]-1,tim[tot]=now;
		p=ch[p][tmp];
	}
}
int Time[N];
int tree[N][32];
int lazy[N][32];
void update(int x){
	if(dep[x]==-1)return;
	int depp=dep[x];
	int tmp=Time[depp];
	if(tmp>tim[x]){
		ch[x][tree[tmp][depp]]=merge(ch[x][0],ch[x][1]);
		ch[x][!tree[tmp][depp]]=0;
		tim[x]=tmp;
	}
	if(lazy[now][depp]^lazy[tim[x]][depp])swap(ch[x][0],ch[x][1]);
	tim[x]=now;
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	update(x),update(y);
	ch[x][0]=merge(ch[x][0],ch[y][0]);
	ch[x][1]=merge(ch[x][1],ch[y][1]);
	ch[y][0]=ch[y][1]=0;
	return x;
}
int query(int x){
	int ans=0;
	int p=1;
	for(int i=30;i>=0;i--){
		update(p);
		int tmp=(x>>i)&1;
		if(ch[p][!tmp]){
			ans|=1<<i;
			p=ch[p][!tmp];
		}
		else p=ch[p][tmp];
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	dep[1]=30;
	now=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		insert(x);
	}
	for(int i=1;i<=m;i++){
		now=i;
		int opt,x;
		cin>>opt>>x;
		for(int j=0;j<=31;j++)lazy[i][j]=lazy[i-1][j];
		switch(opt){
			case 1:insert(x);break;
			case 2:for(int j=0;j<=30;j++)if((x>>j)&1)tree[i][j]=1,Time[j]=i,lazy[i][j]=0;break;
			case 3:for(int j=0;j<=30;j++)if(!((x>>j)&1))tree[i][j]=0,Time[j]=i,lazy[i][j]=0;break;
			case 4:for(int j=0;j<=30;j++)if((x>>j)&1)lazy[i][j]^=1;break;
			default:cout<<query(x)<<"\n";break;
		}
	}
}