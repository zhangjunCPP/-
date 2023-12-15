/*
水题。
一共就 $n$ 行，所以很明显，我们只需要移动最大值前 $n$ 大的列就行了。
然后 $n,m$ 就都降到了 $n$ 的级别。
然后就直接爆搜。
这是道蓝题？2000？
*/
#include<bits/stdc++.h>
using namespace std;
struct node{
	int b[10],Max;
}a[105],tmp[105];
bool cmp(const node &x,const node &y) {return x.Max>y.Max;}
int ans;
int n,m;
int num[105];
int tmp2[100];
void dfs(int k) {
	if(k==min(n,m)+1) {
		memcpy(tmp,a,sizeof tmp);
		for(int i=1;i<=min(n,m);i++) {
			for(int j=1;j<=n;j++)tmp2[j]=tmp[i].b[j];
			for(int j=1;j<=n;j++)tmp[i].b[(j+num[i])%n+1]=tmp2[j];
		}
		int sum=0;
		for(int i=1;i<=n;i++) {
			int MAX=0;
			for(int j=1;j<=min(n,m);j++) MAX=max(MAX,tmp[j].b[i]);
			sum+=MAX;
		}
		ans=max(ans,sum);
		return;
	}
	for(int i=0;i<n;i++) {
		num[k]=i;
		dfs(k+1);
	}
}
void solve(){
	cin>>n>>m;
	ans=0;
	for(int i=1;i<=m;i++)a[i].Max=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){cin>>a[j].b[i];a[j].Max=max(a[j].Max,a[j].b[i]);}
	sort(a+1,a+m+1,cmp);
	dfs(1);
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--) solve();
}
