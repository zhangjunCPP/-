#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000;
int h[N],a[N],p,n,k,m;
struct node {
	int time,id;
	bool operator< (const node &x)const {
		return time>x.time;
	}
};
int tmp[N];
bool check(int mid) {
	priority_queue<node> q;
	for(int i=1; i<=n; i++)tmp[i]=mid;
	for(int i=1; i<=n; i++) {
		if(tmp[i]-m*a[i]>=0)continue;
		q.push(node{tmp[i]/a[i]-1,i});
	}
	int sum=0;
	for(; sum<m*k; sum++) {
		if(q.empty())break;
		node x=q.top();
		q.pop();
		if(x.time<sum/k)return false;
		tmp[x.id]+=p;
		if(tmp[x.id]-m*a[x.id]>=0)continue;
		q.push(node{tmp[x.id]/a[x.id]-1,x.id});
	}
	for(int i=1; i<=n; i++) {
		if(tmp[i]-a[i]*m>=h[i])continue;
		sum+=(h[i]-(tmp[i]-m*a[i])+p-1)/p;
		if(sum>m*k)return false;
	}
	return true;
}
signed main() {
	cin>>n>>m>>k>>p;
	for(int i=1; i<=n; i++) {
		cin>>h[i]>>a[i];
	}
	int l=1,r=1e15;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;
	}
	cout<<l;
}