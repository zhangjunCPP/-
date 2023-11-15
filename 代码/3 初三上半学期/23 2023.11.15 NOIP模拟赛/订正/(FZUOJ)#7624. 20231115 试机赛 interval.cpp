#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
struct node{
	int l,r,id;
	bool operator<(const node&y) const{
		return r>y.r;
	}
}q[N];
bool cmp(const node&x,const node&y) {return x.l<y.l;}
priority_queue<node> q1;
struct node2{
	int i,j;
	bool operator<(const node2&y) const{
		return q[j].r>q[y.j].r;
	}
};
priority_queue<node2> q2;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>q[i].l>>q[i].r;
	for(int i=1;i<=n;i++) q[i].id=i;
	sort(q+1,q+n+1,cmp);
	int ans=0;
	for(int i=1;i<=n;i++) {
		if(!q1.empty()&&(q1.top().r<q[i].l)){
			q2.push({q1.top().id,i});
			q1.pop();
			ans++;
			continue;
		}
		if(!q2.empty()&&(q[q2.top().j].r<q[i].r)){
			auto now=q2.top();
			q2.pop();
			q2.push({now.i,i});
			q1.push(q[now.j]);
			continue;
		}
		q1.push(q[i]);
	}
	cout<<ans;
}
