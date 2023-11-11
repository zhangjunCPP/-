#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],ans[N];
bool flag=true;
bool dfs(int l,int r,int x,int y){
	if(l>r)return true;
	if(a[l]>r+1)return false;
	ans[l]=x+a[l]-l-1;
	bool ans1=dfs(l+1,a[l]-1,x,ans[l]-1);
	bool ans2=dfs(a[l],r,ans[l]+1,y);
	return ans1&&ans2;
}
int read() {
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x;
} 
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	bool flag=dfs(1,n,1,n);
	if(flag)  {
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<"\n";
		return;
	}
	else {
		cout<<"-1\n";
		return ;
	}
}
int main(){
	int T;
	cin>>T;
	while(T--) solve();
}
