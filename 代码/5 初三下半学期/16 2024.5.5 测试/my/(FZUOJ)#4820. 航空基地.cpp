#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
struct node{
	int x,y,d;
}a[N];
int dis(int x,int y){return abs(a[x].x-a[y].x)+abs(a[x].y-a[y].y);}
int ans[N];
const int m=1e9+5;
int f(int x,int y){return (x-1)*m+y;}
map<int,int> mp;
signed main(){
	bool flag=true;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){cin>>a[i].x>>a[i].y>>a[i].d;a[i].x++,a[i].y++;if(a[i].d!=1)flag=false;}
	if(flag){
		for(int i=1;i<=n;i++)mp[f(a[i].x,a[i].y)]=i;
		for(int i=1;i<=n;i++){
			if(mp.count(f(a[i].x,a[i].y-1)))ans[mp[f(a[i].x,a[i].y-1)]]++;
			if(mp.count(f(a[i].x-1,a[i].y)))ans[mp[f(a[i].x-1,a[i].y)]]++;
			if(mp.count(f(a[i].x,a[i].y+1)))ans[mp[f(a[i].x,a[i].y+1)]]++;
			if(mp.count(f(a[i].x+1,a[i].y)))ans[mp[f(a[i].x+1,a[i].y)]]++;
		}
		for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(dis(i,j)<=a[i].d)ans[j]++;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}
/*
T3
考虑算一个点对其他点的贡献？
好像不行。因为我们要输出的是能打击到当前点的个数，所以我们必须要知道一个点能打击的点的具体标号，而不是总个数
-----
暴力
*/