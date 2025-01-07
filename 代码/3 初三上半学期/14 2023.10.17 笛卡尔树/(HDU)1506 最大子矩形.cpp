#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n;
int h[N];
struct node{
	int ls,rs;
}tree[N];
int q[N],top;
void build(){
	q[1]=1,top=1;
	for(int i=2;i<=n;i++) {
		while(top&&h[q[top]]>h[i]) top--;
		if(top==0) tree[i].ls=q[1];
		else {
			tree[i].ls=tree[q[top]].rs;
			tree[q[top]].rs=i;
		}
		q[++top]=i;
	}
}
int ans;
int dfs(int x) {
	if(x==0) return 0;
	int siz=dfs(tree[x].ls)+dfs(tree[x].rs);
	ans=max(ans,(siz+1)*h[x]);
	return siz+1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	build();
	dfs(q[1]);
	cout<<ans;
	return 0;
}