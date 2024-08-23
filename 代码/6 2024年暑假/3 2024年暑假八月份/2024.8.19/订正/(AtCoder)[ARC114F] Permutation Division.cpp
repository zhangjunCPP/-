#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10,limit=1<<22;
int tree[N];
int lowbit(int x){return x&(-x);}
void add(int x,int y) {
	for(int i=x;i<=limit;i+=lowbit(i))tree[i]+=y;
}
int query(int k) {
	int ans=limit;
	for(int i=21;i>=0;i--) {
		if(tree[ans-(1<<i)]<k)k-=tree[ans-(1<<i)];
		else ans-=(1<<i);
	}
	return ans;
}
int a[N];
int pos[N];
bool ed[N];
int id[N],val[N];
bool cmp(const int&x,const int&y) {return a[x]<a[y];}
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i],pos[a[i]]=i;
	ed[n+1]=true;
	if(a[1]<=k) {
		for(int i=1;i<=k;i++)ed[pos[i]]=true;
		for(int i=k;i;i--) {
			cout<<i<<" ";
			for(int j=pos[i]+1;!ed[j];j++)cout<<a[j]<<" ";
		}
		return 0;
	}
	int Max=0;
	for(int i=1;i<=n;i++) {
		if(a[i]>a[1])continue;
		id[i]=upper_bound(val+1,val+n+1,a[i],greater<>{})-val;
		val[id[i]]=a[i];
		Max=max(Max,id[i]);
	}
	if(Max>=k) {
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		return 0;
	}
	int lcp=0;
	int tot=0;
	for(int i=1;i<=a[1];i++) {
		int p=pos[i],c=k-id[p];
		if(c<i) {
			int q=query(i-c);
			if(p<q) {
				if(lcp<q)lcp=q,tot=k+1;
				if(lcp==q&&c<tot)tot=c;
			}
		}
		add(p,1);
	}
	for(int i=1;i<lcp;i++)cout<<a[i]<<" ";
	vector<int>tmp;
	for(int i=lcp;i<=n;i++)tmp.push_back(i);
	sort(tmp.begin(), tmp.end(),cmp);
	for(int i=0;i<tot;i++)ed[tmp[i]]=true;
	for(int i=tot-1;i>=0;i--) {
		cout<<a[tmp[i]]<<" ";
		for(int j=tmp[i]+1;!ed[j];j++)cout<<a[j]<<" ";
	}
}