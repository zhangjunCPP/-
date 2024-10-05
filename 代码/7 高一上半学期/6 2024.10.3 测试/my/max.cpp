#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n;
int a[N],b[N],c[N];
int pos_a[N],pos_b[N];
int lowbit(int x){return x&-x;}
int tree[N];
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
struct node{
	int x,y,z;
	bool operator<(const node&oth)const{if(x!=oth.x)return x<oth.x;if(y!=oth.y)return y<oth.y;if(z!=oth.z)return z<oth.z;return false;}
};
map<node,bool> mp;
void solve(){
	cin>>n;
	mp.clear();
	for(int i=1;i<=n;i++)tree[i]=0;
	bool flag=true;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
		pos_a[a[i]]=i;
		pos_b[b[i]]=i;
		if(a[i]!=b[i])flag=false;
	}
	if(flag){
		int ans=0;
		for(int i=1;i<=n;i++){
			add(c[pos_a[i]],1);
			ans+=query(n)-query(c[pos_a[i]]-1);
		}
		cout<<ans<<"\n";
		return;
	}
	else{
		int ans=0;
		for(int s=1;s<(1<<n);s++){
			int Max1=-1,Max2=-1,Max3=-1;
			for(int j=1;j<=n;j++)if((s>>(j-1))&1)Max1=max(Max1,a[j]),Max2=max(Max2,b[j]),Max3=max(Max3,c[j]);
			if(!mp.count({Max1,Max2,Max3}))ans++,mp[{Max1,Max2,Max3}]=true;
		}
		cout<<ans<<"\n";
	}
}
signed main(){
	freopen("max.in","r",stdin);
	freopen("max.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}