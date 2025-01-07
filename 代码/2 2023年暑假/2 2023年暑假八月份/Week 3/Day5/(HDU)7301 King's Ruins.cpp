#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x;
}
const int N=5e5;
struct node{int x[5],dp,val;}a[N];
bool operator>(const node&s,const node&t){return s.x[0]>=t.x[0]&&s.x[1]>=t.x[1]&&s.x[2]>=t.x[2]&&s.x[3]>=t.x[3]&&s.x[4]>=t.x[4];}
bool cmp(const node&s,const node&t){return s.dp>t.dp;}
void solve(){
	int n;
	n=read();
	for(int i=1;i<=n;i++) {
		for(int j=0;j<5;j++)a[i].x[j]=read();
		a[i].val=read();
		a[i].dp=0;
	}
	int block=sqrt(n);
	int last=1;
	for(int i=1;i<=n;i++){
		if(i%block==0){
			sort(a+1,a+i,cmp);
			last=i;
		}
		for(int j=last;j<i;j++)if(a[i]>a[j]&&a[j].dp>a[i].dp) a[i].dp=a[j].dp;
		for(int j=1;j<last;j++){
			if(a[i].dp>a[j].dp) break;
			if(a[i]>a[j]&&a[j].dp>a[i].dp) a[i].dp=a[j].dp;
		}
		a[i].dp+=a[i].val;
		cout<<a[i].dp<<"\n";
	}
}
signed main(){
	int t;
	t=read();
	while(t--) solve();
}