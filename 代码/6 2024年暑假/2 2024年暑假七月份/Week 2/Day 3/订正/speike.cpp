#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10,INF=1e9;
struct node {
	int x_0,y_0,x_1,y_1;
	bool operator<(const node&oth)const {return x_0<oth.x_0;}
}a[N];
int dis(int x_0,int y_0,int x_1,int y_1) {return abs(x_0-x_1)+abs(y_0-y_1);}
struct node2 {
	int x,y,dis;
	bool operator<(const node2&oth) const {return y<oth.y;}
};
int main() {
	int n,t_x,t_y=0;
	cin>>n>>t_x;
	for(int i=1;i<=n;i++) {
		int x_0,y_0,x_1,y_1;
		cin>>x_0>>y_0>>x_1>>y_1;
		a[i].x_0=min(x_0,x_1);
		a[i].x_1=max(x_0,x_1);
		a[i].y_0=min(y_0,y_1);
		a[i].y_1=max(y_0,y_1);
	}
	sort(a+1,a+n+1);
	set<node2> st;
	st.insert({0,0,0});
	for(int i=1;i<=n;i++) {
		//二分出在该矩形纵范围内的点有哪些
		auto L=st.lower_bound({a[i].x_0,a[i].y_0,0});
		auto R=st.upper_bound({a[i].x_0,a[i].y_1,0});
		int Minl=INF,Minr=INF;
		while(L!=R) {
			Minl=min(Minl,dis(L->x,L->y,a[i].x_0,a[i].y_0)+L->dis);
			Minr=min(Minr,dis(L->x,L->y,a[i].x_0,a[i].y_1)+L->dis);
			st.erase(L++);
		}
		st.insert({a[i].x_0,a[i].y_0,Minl});
		st.insert({a[i].x_0,a[i].y_1,Minr});
	}
	int ans=INF;
	for(auto i:st)ans=min(ans,dis(i.x,i.y,t_x,t_y)+i.dis);
	cout<<ans;
}