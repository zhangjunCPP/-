#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
struct node{
	int id,val;
}a[N];
bool cmp(const node& x,const node& y){
	if(x.val==y.val) return x.id<y.id;
	return x.val>y.val;
}
int q[N],cnt;
int n;
void dfs(int x){
	if(x==1){
		for(int i=q[x]+1;i<=n;i++) cout<<i<<" ";
		cout<<q[x]<<" ";
		return;
	}
	for(int i=q[x]+1;i<q[x-1];i++) cout<<i<<" ";
	dfs(x-1);
	cout<<q[x]<<" ";
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].val;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	int last=n;
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i].id<last){
			q[++cnt]=a[i].id;
			ans+=(last-a[i].id)*a[i].val;
			last=a[i].id;
		}
	}
	cout<<ans<<"\n";
	dfs(cnt);
	return 0;
}
