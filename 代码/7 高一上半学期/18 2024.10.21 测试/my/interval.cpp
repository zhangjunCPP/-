#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
struct node{
	int l,r;
}a[N];
int n;
int tmp[N],tot;
int lowbit(int x){return x&(-x);}
int tree[N];
void add(int x,int val){for(int i=x;i;i-=lowbit(i))tree[i]+=val;}
int query(int x){
	int ans=0;
	for(int i=x;i<=tot;i+=lowbit(i))ans+=tree[i];
	return ans;
}
vector<int>G[N];
void solve(){
	cin>>n;
	tot=0;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		tmp[++tot]=a[i].l;
		tmp[++tot]=a[i].r;
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	for(int i=1;i<=tot;i++)G[i].clear(),tree[i]=0;
	for(int i=1;i<=n;i++){
		a[i].l=lower_bound(tmp+1,tmp+tot+1,a[i].l)-tmp;
		a[i].r=lower_bound(tmp+1,tmp+tot+1,a[i].r)-tmp;
		G[a[i].l].push_back(i);
	}
	int num=0;
	int ans=0x3f3f3f3f;
	for(int i=1;i<=tot;i++){//以i为分割点
		int sum=query(i);
		if(num-sum>0&&n-num>0)ans=min(ans,sum);
		for(int it:G[i])add(a[it].r,1);
		num+=G[i].size();
	}
	if(ans==0x3f3f3f3f)ans=-1;
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
