#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000+10;
int n;
struct node {
	int a,b,c,w;
}a[N];
bool cmp(const node&x,const node&y) {
	if(x.w==y.w)return x.b<y.b;
	return x.w<y.w;
}
int p[26];
bool insert(int x) {
	for(int i=25;i>=0;i--) {
		if((x>>i)&1) {
			if(!p[i]){p[i]=x;return true;}
			x^=p[i];
		}
	}
	return false;
}
pair<int,int> ans={1e9,1e9};
pair<int,int> calc() {
	sort(a+1,a+n+1,cmp);
	memset(p,0,sizeof p);
	int ans1=0,ans2=0;
	for(int i=1;i<=n;i++)if(insert(a[i].a))ans1+=a[i].b,ans2+=a[i].c;
	return {ans1,ans2};
}
void update(pair<int,int>&x,pair<int,int>y) {
	int val1=x.first*x.second,val2=y.first*y.second;
	if(val1>val2||(val1==val2&&x.first>y.first))x=y;
}
int check(int x_1,int y_1,int x_2,int y_2){return x_1*y_2-y_1*x_2;}
void solve(pair<int,int>A,pair<int,int>B) {
	for(int i=1;i<=n;i++)a[i].w=(A.second-B.second)*a[i].b+(B.first-A.first)*a[i].c;
	auto C=calc();
	update(ans,C);
	if(check(B.first-A.first,B.second-A.second,C.first-A.first,C.second-A.second)>=0)return;
	solve(A,C);
	solve(C,B);
}
void solve() {
	ans={1e9,1e9};
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].a>>a[i].b>>a[i].c;
	for(int i=1;i<=n;i++)a[i].w=a[i].b;
	auto A=calc();
	update(ans,A);
	for(int i=1;i<=n;i++)a[i].w=a[i].c;
	auto B=calc();
	update(ans,B);
	solve(A,B);
	cout<<ans.first*ans.second<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}