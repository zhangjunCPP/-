#include<bits/stdc++.h>
using namespace std;
int n,k;
int Max=0;
int ans[100010];
int tmp[100010];
void dfs(int now,int sum){
	if(sum+n-now+1<k) return;
	if(now==n+1) {
		if(sum!=k) return;
		int num=0;
		for(int l=1;l<=n;l++) {
			int cnt=0;
			for(int r=l;r<=n;r++) {
				cnt+=tmp[r];
				if(cnt&1) num++;
			}
		}
		if(num>Max) {
			Max=num;
			for(int i=1;i<=n;i++) ans[i]=tmp[i];
		}
		return;
	}
	tmp[now]=0;
	dfs(now+1,sum);
	tmp[now]=1;
	dfs(now+1,sum+1);
}
int main() {
	freopen("word.in","r",stdin);
	freopen("word.out","w",stdout);
	cin>>n>>k;
	if(k==1) {
		int x=(n+1)/2;
		cout<<(n-x+1)*(x)<<"\n";
		for(int i=1;i<=n;i++) {
			cout<<(i==x)<<" ";
		}
		return 0;
	}
	if(k==2) {
		if(n==1||n==0) {
			cout<<"0\n";
			return 0;
		} 
		int x=1,y=(n+1)/2+1;
		cout<<(y-x)*(n-y+x+1)<<"\n";
		for(int i=1;i<=n;i++) {
			if(i==x||i==y) cout<<"1 ";
			else cout<<"0 ";
		}
		return 0;
	}
	dfs(1,0);
	cout<<Max<<"\n";
	if(Max!=0)for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}