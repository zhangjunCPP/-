#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,L,V;
struct node{
	int d,v,a;
}a[N];
int p[N];
int find_pos(int x){
	//Find the pos near x
	int ans=-1;
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(p[mid]>=x)ans=mid,r=mid-1;
		else l=mid+1;
	}
	return ans;
}
int find_pos2(int x){
	//Find the pos near x
	int ans=-1;
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(p[mid]<=x)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
bool check(int pos,int id){
	//The Car_id move to pos will detect?
	int delta_x=p[pos]-a[id].d; 
	//if(delta_x<0){
	//	//cout<<id<<" "<<pos<<"\n";
	//	return false;}
	if(2*a[id].a*delta_x+a[id].v*a[id].v>V*V)return true;
	return false;
}
int find_l(int l,int r,int id,bool opt){
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,id))ans=mid,r=mid-1;
		else{
			if(opt)l=mid+1;
			else r=mid-1;
		}
	}
	return ans;
}
int find_r(int l,int r,int id,int opt){
	int ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid,id))ans=mid,l=mid+1;
		else {
			if(opt)l=mid+1;
			else r=mid-1;
		}
	}
	return ans;
}
struct node2{
	int l,r;
	int id;
}q[N];
int tot;
void clear(){tot=0;}
void solve(){
	clear();
	cin>>n>>m>>L>>V;
	for(int i=1;i<=n;i++)cin>>a[i].d>>a[i].v>>a[i].a;
	for(int i=1;i<=m;i++)cin>>p[i];
	int ans1=0;
	for(int i=1;i<=n;i++){
		//The Car_i will detect in [l,r]
		int pos1=find_pos(a[i].d);
		if(pos1==-1)continue;
		int pos2=m;
		if(a[i].a<0){
			double delta_x=(1.0*a[i].v*a[i].v)/(2.0*(-a[i].a));
			delta_x+=1.0*a[i].d;
			int tmp_x=floor(delta_x);
			pos2=find_pos2(tmp_x);
		}
		bool opt=(a[i].a>=0);
		int l=find_l(pos1,pos2,i,opt);
		int r=find_r(pos1,pos2,i,opt);
		if(l==-1||r==-1)continue;
		ans1++;
		q[++tot]={l,r,i};
	}
	cout<<ans1<<" ";
	sort(q+1,q+tot+1,[](const node2&x,const node2&y){
		if(x.l==y.l)return x.r<y.r;
		return x.l<y.l;
	});
	//for(int i=1;i<=tot;i++){
	//	cout<<q[i].l<<" "<<q[i].r<<"\n";
	//}
	int ans2=1;
	int last=q[1].r;
	for(int i=2;i<=tot;i++){
		if(q[i].l>last){
			ans2++;
			last=q[i].r;
			continue;
		}
		last=min(last,q[i].r);
	}
	if(ans1==0)ans2=0;
	cout<<m-ans2<<"\n";
}
int main(){
	freopen("detect.in","r",stdin);
	freopen("detect.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}