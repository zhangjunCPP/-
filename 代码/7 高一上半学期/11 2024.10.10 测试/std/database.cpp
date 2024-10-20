#include<bits/stdc++.h>
using namespace std;
int n,m,num=1;
int now,TIME[32],SET[100010][32],REV[100010][32];
int son[7000000][2],dep[7000000],clo[7000000];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
int merge(int x,int y);
void upd(int x)
{
	if(dep[x]==-1)return;
	int d=dep[x],Time=TIME[d];
	if(Time>clo[x]){
		son[x][SET[Time][d]]=merge(son[x][0],son[x][1]);
		son[x][!SET[Time][d]]=0;
		clo[x]=Time;
	}
	if(REV[now][d]^REV[clo[x]][d])
		swap(son[x][0],son[x][1]);
	clo[x]=now;
}
void insert(int x,int pos=1)
{
	for(int i=30;i>=0;i--){
		upd(pos);
		int ch=x>>i&1;
		if(!son[pos][ch]){
			clo[++num]=now;
			dep[son[pos][ch]=num]=dep[pos]-1;
		}
		pos=son[pos][ch];
	}
}
int merge(int x,int y)
{
	if(!x||!y)return x|y;
	upd(x);upd(y);
	son[x][0]=merge(son[x][0],son[y][0]);
	son[x][1]=merge(son[x][1],son[y][1]);
	son[y][0]=son[y][1]=0;
	return x;
}
int ask(int x,int pos=1,int val=0)
{
	for(int i=30;i>=0;i--){
		upd(pos);
		int ch=x>>i&1;
		if(son[pos][!ch])
			val|=1<<i,pos=son[pos][!ch];
		else pos=son[pos][ch];
	}
	return val;
}
int main()
{
	n=read();m=read();
	dep[num=1]=30;now=0;
	for(int i=1;i<=n;i++)
		insert(read());
	for(now=1;now<=m;now++){
		int opt=read(),x=read();
		memcpy(REV[now],REV[now-1],sizeof REV[now]);
		if(opt==1)insert(x);
		if(opt==5)printf("%d\n",ask(x));
		if(opt==2)for(int i=0;i<31;i++)
		if(x>>i&1)SET[now][i]=1,TIME[i]=now,REV[now][i]=0;
		if(opt==3)for(int i=0;i<31;i++)
		if(!(x>>i&1))SET[now][i]=0,TIME[i]=now,REV[now][i]=0;
		if(opt==4)for(int i=0;i<31;i++)
		if(x>>i&1)REV[now][i]^=1;
	}
}