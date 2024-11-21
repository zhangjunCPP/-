#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=3e9;
int n,k;
int a[N],b[N],c[N];
int block;
struct node{
	int val;
	int id1,id2;
	bool operator<(const node&oth)const{return val>oth.val;}
	node(int _val,int _id1,int _id2):val(_val),id1(_id1),id2(_id2){}
};
vector<int> v;
int f(int x){
	int sum=0;
	for(int i=1,j=n;i<=n;i++){
		while(j>0&&b[i]+c[j]>x)j--;
		sum+=j;
	}
	return sum;
}
bool check(int mid){
	int sum=f(mid-a[block]);
	if(sum*block>=k)return true;
	for(int i=1;i<block;i++)sum+=f(mid-a[i]);
	if(sum>=k)return true;
	for(int i=block+1;i<=n;i++)sum+=upper_bound(v.begin(),v.end(),mid-a[i])-v.begin();
	return sum>=k;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	sort(a+1,a+n+1);sort(b+1,b+n+1);sort(c+1,c+n+1);
	block=sqrt(k/n);
	block++;
	block=min(block,n);
	priority_queue<node>q;
	for(int i=1;i<=n;i++)q.emplace(b[i]+c[1],i,1);
	for(int i=1;i<=max(1ll,k/block);i++){
		int val=q.top().val,id1=q.top().id1,id2=q.top().id2;
		q.pop();
		v.push_back(val);
		if(id2<n)q.emplace(b[id1]+c[id2+1],id1,id2+1);
	}
	int l=1,r=INF;
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
}