#include<bits/stdc++.h>
using namespace std;
const int N=3000+10;
struct node{
	int x_1,y_1,x_2,y_2;
}a[N];
bool check(int x,int y,int pos){
	return (x>=a[pos].x_1&&x<=a[pos].x_2&&y>=a[pos].y_1&&y<=a[pos].y_2);
}
bool check(int x,int y){
	if(check(a[x].x_1,a[x].y_1,y)||check(a[x].x_2,a[x].y_2,y)||check(a[x].x_1,a[x].y_2,y)||check(a[x].x_2,a[x].y_1,y))return false;
	if(a[x].x_1>=a[y].x_1&&a[x].x_2<=a[y].x_2&&a[x].y_1<=a[y].y_1&&a[x].y_2>=a[y].y_2)return false;
	swap(x,y);
	if(check(a[x].x_1,a[x].y_1,y)||check(a[x].x_2,a[x].y_2,y)||check(a[x].x_1,a[x].y_2,y)||check(a[x].x_2,a[x].y_1,y))return false;
	if(a[x].x_1>=a[y].x_1&&a[x].x_2<=a[y].x_2&&a[x].y_1<=a[y].y_1&&a[x].y_2>=a[y].y_2)return false;
	return true;
}
bitset<N>vis[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("rectangle.in","r",stdin);
	freopen("rectangle.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].x_1>>a[i].x_2>>a[i].y_1>>a[i].y_2;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(check(i,j))vis[i][j]=true;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)if(vis[i][j])
			ans+=(vis[i]&vis[j]).count();
	cout<<ans;
}