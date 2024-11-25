#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2000+10;
const ll INF=1e18;
int n,m,k,t;
int sx,sy,tx,ty;
int mp[N][N];
struct node{
	int x,y;
	ll val;
	bool operator<(const node&oth)const{return val>oth.val;}
};
ll dis[10][N][N];
bool vis[10][N][N];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
inline bool check(int x,int y){
	if(x>n||x<1||y>m||y<1||!mp[x][y])return false;
	return true;
}
void solve1(){
	priority_queue<node> q;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dis[0][i][j]=INF;
	q.push({sx,sy,0});
	dis[0][sx][sy]=0;
	while(!q.empty()){
		auto now=q.top();q.pop();
		int x=now.x,y=now.y;
		int val=now.val;
		if(vis[0][x][y])continue;
		vis[0][x][y]=true;
		for(int i=0;i<4;i++){
			int Dx=x+dx[i];
			int Dy=y+dy[i];
			if(!check(Dx,Dy))continue;
			if(dis[0][Dx][Dy]>val+1){
				dis[0][Dx][Dy]=val+1;
				q.push({Dx,Dy,dis[0][Dx][Dy]});
			}
		}
		for(int i=1;i<=k;i++){
			for(int ddx=0;ddx<=i;ddx++){
				int ddy=i-ddx;
				auto calc=[&](int x,int y){
					if(check(x,y)&&dis[0][x][y]>val+t){
						dis[0][x][y]=val+t;
						q.push({x,y,dis[0][x][y]});
					}
				};
				int Dx=x+ddx;
				int Dy=y+ddy;
				calc(Dx,Dy);
				Dx=x+ddx;
				Dy=y-ddy;
				calc(Dx,Dy);
				Dx=x-ddx;
				Dy=y+ddy;
				calc(Dx,Dy);
				Dx=x-ddx;
				Dy=y-ddy;
				calc(Dx,Dy);
			}
		}
	}
	if(dis[0][tx][ty]==INF)dis[0][tx][ty]=-1;
	cout<<dis[0][tx][ty];
}
struct node2{
	int x,y,dep;
	ll val;
	bool operator<(const node2&oth)const{return val>oth.val;}
};
void solve2(){
	priority_queue<node2> q;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)for(int l=0;l<=k;l++)dis[l][i][j]=INF;
	q.push({sx,sy,0,0});
	dis[0][sx][sy]=0;
	while(!q.empty()){
		auto now=q.top();q.pop();
		int x=now.x,y=now.y,dep=now.dep;
		int val=now.val;
		// cout<<"("<<x<<","<<y<<")  dep="<<dep<<" val="<<val<<"\n";
		if(vis[dep][x][y])continue;
		vis[dep][x][y]=true;
		if(!dep){
			for(int i=0;i<4;i++){
				int Dx=x+dx[i];
				int Dy=y+dy[i];
				if(x>n||x<1||y>m||y<1)continue;
				if(mp[x][y]&&dis[0][Dx][Dy]>val+1){
					dis[0][Dx][Dy]=val+1;
					q.push({Dx,Dy,0,dis[0][Dx][Dy]});
				}
				if(dis[k-1][Dx][Dy]>val+t){
					dis[k-1][Dx][Dy]=val+t;
					q.push({Dx,Dy,k-1,dis[k-1][Dx][Dy]});
				}
			}
		}
		else{
			for(int i=0;i<4;i++){
				int Dx=x+dx[i];
				int Dy=y+dy[i];
				if(x>n||x<1||y>m||y<1)continue;
				if(dis[dep-1][Dx][Dy]>val){
					dis[dep-1][Dx][Dy]=val;
					q.push({Dx,Dy,dep-1,dis[dep-1][Dx][Dy]});
				}
			}
		}
	}
	ll ans=INF;
	for(int i=0;i<k;i++)ans=min(ans,dis[i][tx][ty]);
	if(ans==INF)ans=-1;
	cout<<ans;
}
int main(){
	freopen("maze.in","r",stdin);
	freopen("maze.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m>>k>>t;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=1;j<=m;j++){
			if(s[j-1]=='.')mp[i][j]=1;
			if(s[j-1]=='#')mp[i][j]=0;
			if(s[j-1]=='S')sx=i,sy=j,mp[i][j]=1;
			if(s[j-1]=='T')tx=i,ty=j,mp[i][j]=1;
		}
	}
	if(n<2000)solve1();
	else solve2();
}