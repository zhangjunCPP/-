/*
区间mex
考虑数据结构？
------
先打个超级暴力，30分不拿白不拿 
*/ 
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
int a[5000000];
int cnt[5000000];
int mex;
void add(int x){
	cnt[x]++;
	if(x==mex)while(cnt[mex])mex++;
}
void del(int x){
	cnt[x]--;
	if(cnt[x]==0)mex=min(mex,x);
}
int main(){
	freopen("maxmex.in","r",stdin);
	freopen("maxmex.out","w",stdout);
	int n;
	n=read();
	int MAX=-1;
	for(int i=1;i<=n;i++){a[i]=read();MAX=max(MAX,a[i]);} 
	int q;
	q=read();
	while(q--){
		int k;
		k=read();
		int ans=-1;
		int l=1,r=k;
		for(int i=0;i<=MAX;i++) cnt[i]=0;
		for(int i=l;i<=r;i++) cnt[a[i]]++;
		mex=0;
		while(cnt[mex]) mex++;
		ans=max(ans,mex);
		while(r<=n){
			add(a[++r]);
			del(a[l++]);
			ans=max(ans,mex);
		}
		printf("%d\n",ans);
	}
	return 0;
}

