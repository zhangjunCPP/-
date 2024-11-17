#include <bits/stdc++.h>
using namespace std;
const int N=50+5;
int col[N][N];
struct node{int x,y,z,c;};
int main(){
	vector<node>ans;
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>col[i][j];
	for(int j=m;j;j--){
		for(int i=1;i<=n;i++){
			int top=(m-j+1)/2*3+(m-j+1)%2;
			for(int l=2;l<=top;l++)ans.push_back({i,j,l,col[i][j]});
			for(int l=j+1;l<m+k;l++)ans.push_back({i,l,top,col[i][j]});
		}
	}
	int top=(m+1)/2*3-1;
	for(int l=top;l>=2;l-=3)for(int i=1;i<=n;i++)for(int j=m;j<m+k;j++)ans.push_back({i,j,l,j-m+1});
	for(int l=top;l>=2;l--)for(int j=m;j<m+k;j++)ans.push_back({n+1,j,l,j-m+1});
	cout<<ans.size()<<"\n";
	for(auto it:ans)cout<<it.x<<" "<<it.y<<" "<<it.z<<" "<<it.c<<"\n";
}