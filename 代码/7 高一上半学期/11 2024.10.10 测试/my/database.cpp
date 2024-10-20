#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int n,m;
int a[N];
struct node{
	int opt,x;
}q[N];
void solve1(){
	for(int i=1;i<=m;i++){
		int opt=q[i].opt;
		if(opt==1)a[++n]=q[i].x;
		else if(opt==2)for(int j=1;j<=n;j++)a[j]|=q[i].x;
		else if(opt==3)for(int j=1;j<=n;j++)a[j]&=q[i].x;
		else if(opt==4)for(int j=1;j<=n;j++)a[j]^=q[i].x;
		else {
			int Max=-1;
			for(int j=1;j<=n;j++)Max=max(Max,a[j]^q[i].x);
			cout<<Max<<"\n";
		}
	}
}
int ch[N][2],tot=1;
void insert(int p,int x,int dep){
	if(dep==-1)return;
	int tmp=(x>>dep)&1;
	if(!ch[p][tmp])ch[p][tmp]=++tot;
	insert(ch[p][tmp],x,dep-1);
}
int query(int p,int x,int dep){
	if(dep==-1)return 0;
	int tmp=(x>>dep)&1;
	if(ch[p][!tmp])return (1<<dep)+query(ch[p][!tmp],x,dep-1);
	else return query(ch[p][tmp],x,dep-1);
}
void solve2(){
	for(int i=1;i<=n;i++)insert(1,a[i],31);
	for(int i=1;i<=m;i++){
		int opt=q[i].opt;
		if(opt==1)insert(1,q[i].x,31);
		else cout<<query(1,q[i].x,31)<<"\n";
	}
}
void solve3(){
	for(int i=1;i<=n;i++)insert(1,a[i],31);
	int now=0;
	for(int i=1;i<=m;i++){
		int opt=q[i].opt;
		if(opt==4)now^=q[i].x;
		else cout<<query(1,q[i].x^now,31)<<"\n";
	}
}
void solve4(){	
	for(int i=1;i<=n;i++)insert(1,a[i],31);
	int now=0;
	for(int i=1;i<=m;i++){
		int opt=q[i].opt;
		if(opt==1)insert(1,q[i].x^now,31);
		else if(opt==4)now^=q[i].x;
		else cout<<query(1,q[i].x^now,31)<<"\n";
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	bool flag[6]={false};
	for(int i=1;i<=m;i++){
		cin>>q[i].opt>>q[i].x;
		flag[q[i].opt]=true;
	}
	if(n<=2000){solve1();return 0;}
	if(flag[1]&&flag[5]&&!flag[2]&&!flag[3]&&!flag[4]){solve2();return 0;}
	if(flag[4]&&flag[5]&&!flag[1]&&!flag[2]&&!flag[3]){solve3();return 0;}
	if(flag[4]&&flag[5]&&flag[1]&&!flag[2]&&!flag[3]){solve4();return 0;}
}