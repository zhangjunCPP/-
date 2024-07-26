#include <bits/stdc++.h>
using namespace std;
const int N=6e6+10;
int dx1[4]={-1,0,0,1};
int dy1[4]={0,-1,1,0};
int dx2[8]={-1,-1,-1,0,0,1,1,1};
int dy2[8]={-1,0,1,-1,1,-1,0,1};
int r,c,n;
int f(int x,int y) {return (x-1)*c+y;}
bool mp[N];
struct node2 {
	int x,y;
	int dis,h;
};
int vis[N];
int main() {
	freopen("stamp.in","r",stdin);
	freopen("stamp.out","w",stdout);
	cin>>r>>c>>n;
	int x_1,y_1,x_2,y_2;
	cin>>x_1>>y_1>>x_2>>y_2;
	for(int i=1;i<=r;i++) {
		string s;
		cin>>s;
		for(int j=1;j<=c;j++)mp[f(i,j)]=(s[j-1]=='#');
	}
	deque<node2>q;
	q.push_back({x_1,y_1,0,0});
	while(true) {
		auto now=q.front();
		q.pop_front();
		int x=now.x,y=now.y;
		int dis=now.dis,h=now.h;
		if(vis[f(x,y)])continue;
		vis[f(x,y)]=true;
		if(x==x_2&&y==y_2) {cout<<dis;return 0;}
		if(h) {
			for(int i=0;i<8;i++) {
				int dx=x+dx2[i];
				int dy=y+dy2[i];
				if(dx<1||dx>r||dy<1||dy>c)continue;
				if(!vis[f(dx,dy)])q.push_back({dx,dy,dis,h-1});
			}
		}
		else {
			for(int i=0;i<4;i++) {
				int dx=x+dx1[i];
				int dy=y+dy1[i];
				if(dx<1||dx>r||dy<1||dy>c)continue;
				if(!vis[f(dx,dy)]) {
					if(mp[f(dx,dy)])q.push_back({dx,dy,dis+1,n-1});
					else q.push_front({dx,dy,dis,0});
				}
			}
		}
	}
}