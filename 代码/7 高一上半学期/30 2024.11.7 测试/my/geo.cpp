#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
const int INF=5e18;
struct node{
	int w,h;
}a[N];
int st[N][25],lg[N];
void init(int n){
	for(int i=1;i<=n;i++)st[i][0]=a[i+1].w-a[i].w;
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
}
int ask(int l,int r){
	if(l>r)return 1;
	int tmp=lg[r-l+1];
	return min(st[l][tmp],st[r-(1<<tmp)+1][tmp]);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	bool flag=true;
	for(int i=1;i<=n;i++){
		cin>>a[i].w>>a[i].h;
		if(a[i].h!=1)flag=false;
	}
	if(flag){
		init(n-1);
		while(q--){
			int l,r;
			cin>>l>>r;
			cout<<ask(l,r-1)*2<<"\n";
		}
		return 0;
	}
	while(q--){
		int l,r;
		cin>>l>>r;
		int Min=INF;
		for(int i=l;i<=r;i++){
			for(int j=i+1;j<=r;j++){
				Min=min(Min,(a[j].w-a[i].w)*(a[i].h+a[j].h));
			}
		}
		cout<<Min<<"\n";
	}
	return 0;
}