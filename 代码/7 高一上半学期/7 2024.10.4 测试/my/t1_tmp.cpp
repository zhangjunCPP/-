#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n;
int id[N];
int ans[N];
int tree[N];
int lowbit(int x){return x&-x;}
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){int ans=0;for(int i=x;i;i-=lowbit(i))ans+=tree[i];return ans;}
int main(){
	freopen("ant.in","r",stdin);
	freopen("ant.out","w",stdout);
	string s;
	cin>>n>>s;
	int cnt=0
	for(int i=0;i<n;i++)if(s[i]=='L')cnt++;
	vector<int> L,R;
	for(int i=0;i<n;i++){
		if(s[i]=='L')L.push_back(i+1);
		else R.push_back(i+1);
	}
	for(int i=0;i<L.size();i++)id[L[i]]=i+1;
	for(int i=0;i<R.size();i++)id[R[i]]=cnt+i+1;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='P')add(n-id[i]+1,1);
		else ans[i]=query(n-i+1)+query(n-i);
	}
	memset(tree,0,sizeof tree);
	for(int i=n;i;i--){
		if(s[i-1]=='L')add(id[i],1);
		else ans[i]=query(i-1)+query(i);
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
}