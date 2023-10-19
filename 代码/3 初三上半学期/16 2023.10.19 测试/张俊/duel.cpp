#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
struct node{
	int x,y,z;
}a[N];
int col[N];
int n,m;
void dfs(int now){
	if(now>m) {
		for(int i=1;i<=n;i++) {
			if(col[i]==1) cout<<"C";
			if(col[i]==2) cout<<"E";
			if(col[i]==3) cout<<"Z";
			if(col[i]==4) cout<<"F";
		}
		exit(0);
		return ;	
	}
	int x=a[now].x,y=a[now].y;
	if(a[now].z==0) {
		if(col[x]){
			if(col[x]==1){
				if(col[y]) dfs(now+1);
				else {
					for(int i=1;i<=4;i++) {
						col[y]=i;
						dfs(now+1);
						col[y]=0;
					}
				}
			}
			else if(col[x]==2){
				if(col[y]) {
					if(col[y]==1||col[y]==4) return;
					else dfs(now+1);
				}
				else {
					col[y]=2; dfs(now+1); col[y]=0;
					col[y]=3; dfs(now+1); col[y]=0;
				}
			}
			else if(col[x]==3){
				if(col[y]) {
					if(col[y]!=3) return;
					else dfs(now+1);
				}
				else {
					col[y]=3; dfs(now+1); col[y]=0;
				}
			}
			else if(col[x]==4){
				if(col[y]) {
					if(col[y]==1||col[y]==2) return;
					else dfs(now+1);
				}
				else {
					col[y]=3; dfs(now+1); col[y]=0;
					col[y]=4; dfs(now+1); col[y]=0;
				}
			}
		}
		else if(col[y]){
			if(col[y]==1){
				if(col[x]) {
					if(col[x]!=1) return;
					else dfs(now+1);
				}
				else {
					col[x]=1; dfs(now+1); col[x]=0;
				}
			}
			else if(col[y]==2){
				if(col[x]){
					if(col[x]==3||col[x]==4) return;
					else dfs(now+1);
				}
				else {
					col[x]=1; dfs(now+1); col[x]=0;
					col[x]=2; dfs(now+1); col[x]=0;
				}
			}
			else if(col[y]==3){
				if(col[x]) dfs(now+1);
				else {
					for(int i=1;i<=4;i++) {
						col[x]=i; dfs(now+1); col[x]=0;
					}
				}
			}
			else if(col[y]==4){
				if(col[x]){
					if(col[x]==2||col[x]==3) return;
					else dfs(now+1);
				}
			}
		}
		else {
			col[x]=1;col[y]=1; dfs(now+1);
			col[x]=1;col[y]=2; dfs(now+1);
			col[x]=1;col[y]=3; dfs(now+1);
			col[x]=1;col[y]=4; dfs(now+1);
			col[x]=2;col[y]=2; dfs(now+1);
			col[x]=2;col[y]=3; dfs(now+1);
			col[x]=3;col[y]=3; dfs(now+1);
			col[x]=4;col[y]=3; dfs(now+1);	
			col[x]=4;col[y]=4; dfs(now+1);
			col[x]=0,col[y]=0;
		}
	}
	else {
		if(col[x]) {
			if(col[x]==1) return;
			else if(col[x]==2) {
				
				if(col[y]) {
					if(col[y]==2||col[y]==3) return;
					else dfs(now+1);
				}
				else{
					col[y]=1;dfs(now+1);col[y]=0; 
					col[y]=4;dfs(now+1);col[y]=0;
				}
			}
			else if(col[x]==3) {
				
				if(col[y]) {
					if(col[y]==3) return;
					else dfs(now+1);
				}
				else {
					col[y]=1;dfs(now+1);col[y]=0;
					col[y]=2;dfs(now+1);col[y]=0;
					col[y]=4;dfs(now+1);col[y]=0;
				}
			}
			else if(col[x]==4){
				if(col[y]) {
					if(col[y]==3||col[y]==4) return;
					else dfs(now+1);
				}
				else {
					col[y]=1;dfs(now+1);col[y]=0;
					col[y]=2;dfs(now+1);col[y]=0;
				}
			}
		}
		else if(col[y]){
			if(col[y]==1) {
				if(col[x]) {
					if(col[x]==1) return;
					else dfs(now+1);
				} 
				else {
					col[x]=2;dfs(now+1);col[x]=0;
					col[x]=3;dfs(now+1);col[x]=0;
					col[x]=4;dfs(now+1);col[x]=0;
				}
			}
			else if(col[y]==2) {
				
				if(col[x]) {
					if(col[x]==1||col[x]==2) return;
					else dfs(now+1);
				}
				else {
					col[x]=3;dfs(now+1);col[x]=0;
					col[x]=4;dfs(now+1);col[x]=0;
				}
			}
			else if(col[y]==3) return;
			else if(col[y]==4) {
				if(col[x]) {
					if(col[x]==1||col[x]==4) return ;
					else dfs(now+1);
				}
				else {
					col[x]=2;dfs(now+1);col[x]=0;
					col[x]=3;dfs(now+1);col[x]=0;
				}
			}
		}
		else {
			col[x]=2;col[y]=1; dfs(now+1);
			col[x]=2;col[y]=4; dfs(now+1);
			col[x]=3;col[y]=1; dfs(now+1);
			col[x]=3;col[y]=2; dfs(now+1);
			col[x]=3;col[y]=4; dfs(now+1);
			col[x]=4;col[y]=1; dfs(now+1);
			col[x]=4;col[y]=2; dfs(now+1);
			col[x]=0,col[y]=0;
		}
	}
	return;
}
void solve() {
	dfs(1); 
	cout<<"NO";
}
int main(){
	freopen("duel.in","r",stdin);
	freopen("duel.out","w",stdout);
	cin>>n>>m; 
	for(int i=1;i<=m;i++) cin>>a[i].x>>a[i].y>>a[i].z;
	solve();


	return 0;
}