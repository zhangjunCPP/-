#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int ty,n,C,ct1,ct2,st[N],a1[N],b1[N],a[N],b[N],c[N],f[N][N],g[N][N];char s[N],t[N];
void qm(int &x,int y){x=min(x,y);}
int get(int x,int y){int len=abs(x-y);
	return (len/2)*(C+4)+(len&1)*(C+3);
}
int top;struct node{int l,r;}as[1000005];
void solve(int x,int y){
	if(x==0)return ;
	if(g[x][y]==2)st[x]=b[x-y];else st[x]=a[y];
	if(g[x][y]==2)solve(x-1,y);
	else solve(x-1,y-1);
}
void upd(int u,int v){
	if(u>v){
		while(u>v+1){
			as[++top]={u-2,u};
			u-=2;
		}
		if(u!=v)as[++top]={v,u};
	}else {
		while(u<v-1){
			as[++top]={u,u+2};
			u+=2;
		}
		if(u!=v)as[++top]={u,v};
	}
}
int main(){

	scanf("%d%d%d%s%s",&ty,&n,&C,s+1,t+1);
	for(int i=1;i<=n;i++)if(t[i]=='B'){
		if(i&1)a[++ct1]=i;else b[++ct2]=i;
	}
	for(int i=1,j=1;i<=ct1||j<=ct2;){
		if(i>ct1||a[i]>b[j]&&j<=ct2)b1[j]=i,j++;
		else a1[i]=j,i++;
	}
	//	for(int i=1;i<=ct1;i++)cout<<a[i]<<" "<<a1[i]<<endl;
	//	for(int i=1;i<=ct2;i++)cout<<b[i]<<" "<<b1[i]<<endl;
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int ct=1,i=0;ct<=n;ct++)if(s[ct]=='B'){i++,c[i]=ct;
		for(int x=0;x<=ct1;x++)if(x<=f[n+1][0]){int y=i-1-x;
			if(x<ct1){
				int v=get(ct,a[x+1])+f[i-1][x]+max(y-a1[x+1]+1,0);
				if(v<f[i][x+1]){f[i][x+1]=v,g[i][x]=1;}
			}
			if(y<ct2){
				int v=get(ct,b[y+1])+f[i-1][x]+max(x-b1[y+1]+1,0);
				if(v<f[i][x]){f[i][x]=v,g[i][x]=2;}
			}
		}
	}
	//	cout<<f[ct1+ct2][ct1]<<endl;
	solve(ct1+ct2,ct1);
	for(int i=ct1+ct2;i>=1;i--)if(st[i]>c[i])upd(c[i],st[i]);
	for(int i=1;i<=ct1+ct2;i++)if(st[i]<c[i])upd(c[i],st[i]);
	printf("%d\n",top);
	for(int i=1;i<=top;i++)printf("%d %d\n",as[i].l,as[i].r);
	return 0;
}