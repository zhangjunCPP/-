#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=50+10;
const int INF=1e10;
int n,k;
int calc(int x_1,int y_1,int x_2,int y_2,int x,int y){
	if(x_1<=0||y_1<=0||x_2<=0||y_2<=0)return -1;
	if(x_1>n||y_1>n||x_2>n||y_2>n)return -1;
	//从 (x_1,y_1) 到 (x_2,y_2) 范围内，有 x 个黑点变为白点，有 y 个白点变为黑点、
	int tot1=0,tot2=0;
	int len_x=(x_2-x_1+1),len_y=(y_2-y_1+1);
	if(len_x&1){
		if((x_1+y_1)&1)tot1=len_x*(len_y/2)+(len_y%2)*((len_x+1)/2);
		else tot1=len_x*(len_y/2)+(len_y%2)*(len_x/2);
	}
	else tot1=(len_x/2)*len_y;
	tot2=len_x*len_y-tot1;
	// cout<<x_1<<" "<<y_1<<" "<<x_2<<" "<<y_2<<" "<<x<<" "<<y<<"\n";
	return llabs((tot1-x+y)-(tot2-y+x));
}
struct node{
	int x,y;
}point[N];
bool cmp(const node&x,const node&y){
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
int f(int Min_x,int Min_y,int Max_x,int Max_y){
	int tot[2]={0};
	for(int i=1;i<=k;i++){
		if(point[i].x>=Min_x&&point[i].x<=Max_x&&point[i].y>=Min_y&&point[i].y<=Max_y)tot[(point[i].x+point[i].y)&1]++;
	}
	return calc(Min_x,Min_y,Max_x,Max_y,tot[1],tot[0]);
}
void solve(){
	cin>>n>>k;
	for(int i=1;i<=k;i++)cin>>point[i].x>>point[i].y;
	int ans=1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			for(int l=1;l<=k;l++){
				for(int m=1;m<=k;m++){
					int Min_x=min({point[i].x,point[j].x,point[l].x,point[m].x});
					int Min_y=min({point[i].y,point[j].y,point[l].y,point[m].y});
					int Max_x=max({point[i].x,point[j].x,point[l].x,point[m].x});
					int Max_y=max({point[i].y,point[j].y,point[l].y,point[m].y});
					ans=max(ans,f(Min_x,Min_y,Max_x,Max_y));
					ans=max(ans,f(Min_x,Min_y,Max_x,Max_y+1));
					ans=max(ans,f(Min_x,Min_y,Max_x+1,Max_y));
					ans=max(ans,f(Min_x,Min_y,Max_x+1,Max_y+1));
					ans=max(ans,f(Min_x,Min_y-1,Max_x,Max_y));
					ans=max(ans,f(Min_x,Min_y-1,Max_x,Max_y+1));
					ans=max(ans,f(Min_x,Min_y-1,Max_x+1,Max_y));
					ans=max(ans,f(Min_x,Min_y-1,Max_x+1,Max_y+1));
					ans=max(ans,f(Min_x-1,Min_y,Max_x,Max_y));
					ans=max(ans,f(Min_x-1,Min_y,Max_x,Max_y+1));
					ans=max(ans,f(Min_x-1,Min_y,Max_x+1,Max_y));
					ans=max(ans,f(Min_x-1,Min_y,Max_x+1,Max_y+1));
					ans=max(ans,f(Min_x-1,Min_y-1,Max_x,Max_y));
					ans=max(ans,f(Min_x-1,Min_y-1,Max_x,Max_y+1));
					ans=max(ans,f(Min_x-1,Min_y-1,Max_x+1,Max_y));
					ans=max(ans,f(Min_x-1,Min_y-1,Max_x+1,Max_y+1));
				}
			}
		}
	}
	cout<<ans<<"\n";
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}