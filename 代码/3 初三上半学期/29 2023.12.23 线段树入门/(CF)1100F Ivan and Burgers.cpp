#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
struct node{
	int l,r,id;
}q[N];
bool cmp(const node &x,const node &y){return x.r<y.r;}

int pos[N],val[N];
void insert(int x,int id){
	for(int i=25;i>=0;i--){
		if(x&(1<<i)){
			if(!pos[i]){
				pos[i]=id;
				val[i]=x;
				return;
			}
			if(pos[i]<id) swap(pos[i],id),swap(val[i],x);
			x^=val[i];
		}
	}
}
int query(int l){
	int ans=0;
	for(int i=25;i>=0;i--){
		if(pos[i]>=l&&((ans^val[i])>ans))ans=ans^val[i];
	}
	return ans;
}
int ans[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int Q;
	cin>>Q;
	for(int i=1;i<=Q;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+Q+1,cmp);
	int r=0;
	for(int i=1;i<=Q;i++){
		while(r<q[i].r){
			r++;
			insert(a[r],r);
		}
		ans[q[i].id]=query(q[i].l);
	}
	for(int i=1;i<=Q;i++)cout<<ans[i]<<"\n";
}
