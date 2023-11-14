#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
int fa[N];
int find(int x) {
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	fa[x]=y;
}
struct node{
	int u,v,w;
}a[N];
bool cmp(const node &x,const node &y) {return x.w<y.w;}
bool vis[N];
int main() {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)cin>>a[i].u>>a[i].v;
	int s,t,ds,dt;
	cin>>s>>t>>ds>>dt;

	int tmp1,tmp2;
	if(ds>dt) tmp1=1,tmp2=2;
	else tmp1=2,tmp2=1;
	for(int i=1;i<=m;i++){
		if(a[i].u==s||a[i].v==s) a[i].w=tmp1;
		if(a[i].u==t||a[i].v==t) a[i].w=tmp2;
	}
	sort(a+1,a+m+1,cmp);

	int cnt=0;
	int sum1=0,sum2=0;
	for(int i=1;i<=m;i++) {
		int fx=find(a[i].u),fy=find(a[i].v);
		if(a[i].w==0) {
			if(fx!=fy) {
				cnt++;
				vis[i]=true;
				merge(a[i].u,a[i].v);
			}
		}
		else {
			if(fx!=fy){
				if(a[i].u==s||a[i].v==s) {
					if(sum1==ds) continue;
					sum1++;
				}
				if(a[i].u==t||a[i].v==t) {
					if(sum2==dt) continue;
					sum2++;
				}
				cnt++;
				vis[i]=true;
				merge(a[i].u,a[i].v);
			}
		}
	}
	if(sum1<=ds&&sum2<=dt&&cnt==n-1) {
		cout<<"Yes\n";
		for(int i=1;i<=m;i++) {if(vis[i]) cout<<a[i].u<<" "<<a[i].v<<"\n";}
	}
	else {
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=m;i++)vis[i]=false;
		if(ds>dt) tmp1=2,tmp2=1;
		else tmp1=1,tmp2=2;
		for(int i=1;i<=m;i++){
			if(a[i].u==s||a[i].v==s) a[i].w=tmp1;
			if(a[i].u==t||a[i].v==t) a[i].w=tmp2;
		}
		sort(a+1,a+m+1,cmp);
		cnt=0;
		sum1=0,sum2=0;
		for(int i=1;i<=m;i++) {
			int fx=find(a[i].u),fy=find(a[i].v);
			if(a[i].w==0) {
				if(fx!=fy) {
					cnt++;
					vis[i]=true;
					merge(a[i].u,a[i].v);
				}
			}
			else {
				if(fx!=fy){
					if(a[i].u==s||a[i].v==s) {
						if(sum1==ds) continue;
						sum1++;
					}
					if(a[i].u==t||a[i].v==t) {
						if(sum2==dt) continue;
						sum2++;
					}
					cnt++;
					vis[i]=true;
					merge(a[i].u,a[i].v);
				}
			}
		}
		if(sum1<=ds&&sum2<=dt&&cnt==n-1) {
			cout<<"Yes\n";
			for(int i=1;i<=m;i++) {if(vis[i]) cout<<a[i].u<<" "<<a[i].v<<"\n";}
		}
		else cout<<"No\n";
	}


}