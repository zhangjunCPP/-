#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n;
int lowbit(int x){return x&-x;}
int tree[N];
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]+=val;}
int query(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i))ans+=tree[i];
	return ans;
}
int a[N];
void solve(){
	string s;
	cin>>n>>s;
	int Min=1,Max=n;
	for(int i=0;i<n;i++){
		if(s[i]=='0')a[i+1]=Max,Max--;
		else {
			int j=i;
			while(s[j]=='1'&&j<n)j++;
			// s[i~j-1]=1;s[j]=0
			for(int l=j+1;l>=i+1;l--)a[l]=Max,Max--;
			i=j;
		}
	}
	for(int i=1;i<=n;i++)tree[i]=0;
	int ans=0;
	for(int i=n;i>=1;i--){
		ans+=query(a[i]);
		add(a[i],1);
	}
	cout<<ans<<"\n";
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	cout<<"\n";
}
signed main(){
	freopen("inv.in","r",stdin);
	freopen("inv.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}