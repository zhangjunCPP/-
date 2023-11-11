#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N],ans[N];
bool flag=true;
void dfs(int l,int r,int x,int y){
	if(!flag) return;
	if(l>r)return;
	if(a[r]!=r+1) {
		flag=false;
		return;
	}
	if(x==y){
		if(l!=r){
			flag=false;
			return;
		}
	}
	if(l==r){
		if(x>y) {
			flag=false;
			return;
		} 
		ans[l]=x;
		return;
	}
	if(x>y)return;
	for(int i=l;i<=r-1;i++) {
		if(a[i]>r+1){
			flag=false;
			return;
		}
	}
	int now=y;
	for(int i=l;i<=r-1;i++) {
		if(a[i]==r+1) {
			ans[i]=now;
			now--;
		}
	}
	ans[r]=now;
	now--;
	int last1=l-1;
	int last2=x-1;
	for(int i=l;i<=r-1;i++) {
		if(a[i]==r+1) {
			int len=i-1-(last1+1)+1;
			dfs(last1+1,i-1,last2+1,last2+1+len-1);
			if(flag==false) return; 
			last1=i;
			last2=last2+1+len-1;
		}
	}
	int len=r-1-(last1+1)+1;
	if(now!=last2+1+len-1) {
		flag=false;
		return;
	}
	dfs(last1+1,r-1,last2+1,now);
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
	flag=true;
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) ans[i]=0;
	dfs(1,n,1,n);
	if(!flag){
		cout<<"-1\n";
		return;
	} 
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
int main(){
	freopen("cool.in","r",stdin);
	freopen("cool.out","w",stdout);
	int T;
	cin>>T;
	while(T--) solve();
}
