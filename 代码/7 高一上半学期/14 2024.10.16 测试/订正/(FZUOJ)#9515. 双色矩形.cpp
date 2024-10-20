#include<bits/stdc++.h>
using namespace std;
const int N=200+10;
struct node{
	int x,y;
}a[N];
int tmp_x[N],tot_x;
int tmp_y[N],tot_y;
int s[N][N];
int calc(int x1,int y1,int x2,int y2){
	return s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1];
}
int f(int x1,int y1,int x2,int y2){
	if((!((x2-x1+1)&1))||(!((y2-y1+1)&1)))return 0;
	if((x1+y1)&1)return 1;
	return -1;
}
void solve(){
	tot_x=tot_y=0;
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i].x>>a[i].y;
		tmp_x[++tot_x]=a[i].x;
		tmp_y[++tot_y]=a[i].y;
		if(a[i].x>1)tmp_x[++tot_x]=a[i].x-1;
		if(a[i].x<n)tmp_x[++tot_x]=a[i].x+1;
		if(a[i].y>1)tmp_y[++tot_y]=a[i].y-1;
		if(a[i].y<n)tmp_y[++tot_y]=a[i].y+1;
	}
	sort(tmp_x+1,tmp_x+tot_x+1);
	sort(tmp_y+1,tmp_y+tot_y+1);
	tot_x=unique(tmp_x+1,tmp_x+tot_x+1)-tmp_x-1;
	tot_y=unique(tmp_y+1,tmp_y+tot_y+1)-tmp_y-1;
	memset(s,0,sizeof s);
	for(int i=1;i<=k;i++){
		int x=lower_bound(tmp_x+1,tmp_x+tot_x+1,a[i].x)-tmp_x;
		int y=lower_bound(tmp_y+1,tmp_y+tot_y+1,a[i].y)-tmp_y;
		if((a[i].x+a[i].y)&1)s[x][y]-=2;
		else s[x][y]+=2;
	}
	for(int i=1;i<=tot_x;i++)
		for(int j=1;j<=tot_y;j++)
			s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	int ans=1;
	for(int x1=1;x1<=tot_x;x1++)
		for(int y1=1;y1<=tot_y;y1++)
			for(int x2=x1;x2<=tot_x;x2++)
				for(int y2=y1;y2<=tot_y;y2++)
					ans=max(ans,abs(calc(x1,y1,x2,y2)+f(tmp_x[x1],tmp_y[y1],tmp_x[x2],tmp_y[y2])));
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}