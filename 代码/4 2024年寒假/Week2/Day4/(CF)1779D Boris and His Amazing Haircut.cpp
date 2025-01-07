#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

int a[N],b[N];
int tree[N*4];
void build(int k,int l,int r){
	if(l==r){tree[k]=b[l];return;}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=max(tree[k<<1],tree[k<<1|1]);
}
int query(int k,int l,int r,int x,int y){
	if(l>y||r<x) return -1;
	if(x<=l&&y>=r) return tree[k];
	int mid=(l+r)>>1;
	return max(query(k<<1,l,mid,x,y),query(k<<1|1,mid+1,r,x,y));
}
map<int,int> cnt1,cnt2;
map<int,int> mp;
void solve(){
	mp.clear();
	cnt1.clear();
	cnt2.clear();
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	build(1,1,n);
	int m;
	cin>>m;
	for(int i=1;i<=m;i++) {
		int x;
		cin>>x;
		cnt1[x]++;
	}
	for(int i=1;i<=n;i++)if(a[i]<b[i]){puts("NO");return;}
	for(int i=1;i<=n;i++){
		if(a[i]==b[i]) continue;
		if(!mp.count(b[i]))mp[b[i]]=i;
		else{
			int Max=query(1,1,n,mp[b[i]],i);
			if(Max>b[i]) cnt2[b[i]]++;
			mp[b[i]]=i;
		}
	}
	for(auto i:mp)cnt2[i.first]++;
	for(auto i:cnt2)if(cnt1[i.first]<i.second){puts("NO");return;}
	puts("YES");
	return;

}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}