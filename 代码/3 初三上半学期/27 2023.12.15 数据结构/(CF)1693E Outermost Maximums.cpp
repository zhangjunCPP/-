#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n;
int tree[N];//维护不确定的个数
int lowbit(int x) {return x&(-x);}
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
int a[N];
vector<int> G[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],G[a[i]].push_back(i);
	int ans=0;
	int l=1,r=n;//l,r表示不确定的位置的最左/最右
	for(int i=n;i>=1;i--){
		if(!G[i].empty()) {
			int L=G[i][0],R=G[i][G[i].size()-1];
			ans+=G[i].size()+query(R)-query(L);
			if(r<L) ans+=query(L)-query(r),l=r+1,r=R;
			else if(R<l) ans+=query(l-1)-query(R),r=l-1,l=L;
			else l=L,r=R;
			for(int j:G[i]) add(j,1);
		}
	}
	cout<<ans;
}