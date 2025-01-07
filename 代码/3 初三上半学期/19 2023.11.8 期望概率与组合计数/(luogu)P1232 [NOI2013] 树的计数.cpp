#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int dfn[N],pos[N];
int read(){int x;cin>>x;return x;}
int sum[N];
void add(int x,int y) {sum[x]++,sum[y+1]--;}
int main() {
	int n=read();
	for(int i=1;i<=n;i++) dfn[read()]=i;
	for(int i=1;i<=n;i++) pos[dfn[read()]]=i;
	for(int i=1;i<=n;i++) dfn[pos[i]]=i;
	double ans=0;
	ans++;add(1,1);
	for(int i=1;i<n;i++) {
		if(dfn[i]>dfn[i+1]) ans++,add(i,i);
		if(pos[i]<pos[i+1]-1) add(pos[i],pos[i+1]-1);
	}
	int now=0;
	for(int i=1;i<n;i++) {now+=sum[i];if(now==0) ans+=0.5;}
	ans++;
	printf("%.3lf",ans);
	return 0;
}