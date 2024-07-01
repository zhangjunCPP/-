#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int n,k;
int h[N];
int s[N],t[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	cin>>k;
	for(int i=1;i<=k;i++)cin>>s[i]>>t[i];
}
/*
感觉像个二分
观察到，每次只能移动一枚棋子。
所以如果这枚棋子原位置比现位置权值大，那当前状态就可以不用考虑。
同时，由于树上两点路径唯一，所以我们可以将棋子先移动到距离目标位置较近的地方，且路径上的点的权值均小于起始位置
不对。
发现，我们是可以绕路走的。如果一个点的权值非常小，那么我们可以先走到那个点，等其他点走完后再原路返回
-------
放弃
*/