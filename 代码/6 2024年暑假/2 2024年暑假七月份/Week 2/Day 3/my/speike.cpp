// #include<bits/stdc++.h>
// #define x0 x_0
// #define x1 x_1
// #define y0 y_0
// #define y1 y_1

// using namespace std;
// const int N=5e5+10;
// struct node{
// 	int x0,y0,x1,y1;
// }a[N];
// bool cmp(const node&x,const node&y){
// 	if(x.x0==y.x0)return x.y0<y.y0;
// 	else return x.x0<y.x0;
// }
// vector<int> tmp;
// struct node2{
// 	int val,lazy;
// }tree[N<<2];
// int ls(int k){return k<<1;}
// int rs(int k){return k<<1|1;}
// void modify(int k,int v){tree[k].val=tree[k].lazy=v;}
// void pushdown(int k){
// 	if(tree[k].lazy){
// 		modify(ls(k),tree[k].lazy);
// 		modify(rs(k),tree[k].lazy);
// 		tree[k].lazy=0;
// 	}
// }
// void update(int k,int l,int r,int x,int y,int v){
// 	if(x<=l&&y>=r)modify(k,v);
// 	pushdown(k);
// 	int mid=(l+r)>>1;
// 	if(x<=mid)update(ls(k),l,mid,x,y,v);
// 	if(y>mid)update(rs(k),mid+1,r,x,y,v);
// }
// int query(int k,int l,int r,int x){
// 	if(l==r)return tree[k].val;
// 	int mid=(l+r)>>1;
// 	pushdown(k);
// 	if(x<=mid)return query(ls(k),l,mid,x);
// 	else return query(rs(k),mid+1,r,x);
// }
// int main(){
// 	int n,t;
// 	cin>>n>>t;
// 	if(n==0){cout<<t;return 0;}
// 	for(int i=1;i<=n;i++){
// 		int x0,x1,y0,y1;
// 		cin>>x0>>y0>>x1>>y1;
// 		a[i].x0=min(x0,x1);
// 		a[i].x1=max(x0,x1);
// 		a[i].y0=min(y0,y1);
// 		a[i].y1=max(y0,y1);
// 		tmp.push_back(a[i].y0);
// 		tmp.push_back(a[i].y1);
// 	}
// 	sort(a+1,a+n+1,cmp);
// 	tmp.push_back(0);
// 	sort(tmp.begin(),tmp.end());
// 	tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
// 	for(int i=n;i>=1;i--){
// 		//求出到矩形两个端点的距离
// 		int y0=lower_bound(tmp.begin(),tmp.end(),a[i].y0)-tmp.begin();
// 		int y1=lower_bound(tmp.begin(),tmp.end(),a[i].y1)-tmp.begin();

// 	}


// }
// /*
// 肯定要用扫描线
// 区间修改，单点查询

// */



#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int main() {
	freopen("speike.in","r",stdin);
	freopen("speike.out","w",stdout);
	int n,t;
	cin>>n>>t;
	if(n==0){cout<<abs(t);return 0;}
	if(n==1){
		int x_0,y_0,x_1,y_1;
		cin>>x_0>>y_0>>x_1>>y_1;
		int tmp1=min(x_0,x_1),tmp2=max(x_0,x_1);
		x_0=tmp1;
		x_1=tmp2;
		tmp1=min(y_0,y_1),tmp2=max(y_0,y_1);
		y_0=tmp1;
		y_1=tmp2;
		if(y_0>=0||y_1<=0)cout<<abs(t);
		else cout<<abs(t)+2*min(-y_0,y_1);
		return 0;
	}
	int ans=abs(t);
	for(int i=1;i<=n;i++) {
		int x_0,y_0,x_1,y_1;
		cin>>x_0>>y_0>>x_1>>y_1;
		int tmp1=min(x_0,x_1),tmp2=max(x_0,x_1);
		x_0=tmp1;
		x_1=tmp2;
		tmp1=min(y_0,y_1),tmp2=max(y_0,y_1);
		y_0=tmp1;
		y_1=tmp2;
		ans+=2*min(-y_0,y_1);
	}
	cout<<ans;
}