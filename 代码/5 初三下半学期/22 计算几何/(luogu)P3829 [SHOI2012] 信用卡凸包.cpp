#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const double eps=1e-6;
const double pi=acos(-1);

int sgn(double x){return x<-eps?-1:x>eps;}
struct point{
	double x,y;
	void init(){cin>>x>>y;}
	double phi(){return atan2(y,x);}//辐角
	double len(){return hypot(x,y);}//模长
	point operator*(const double&k) const{return point{x*k,y*k};}
	point operator+(const point&oth) const{return point{x+oth.x,y+oth.y};}
	point operator-(const point&oth) const{return point{x-oth.x,y-oth.y};}
	double operator*(const point&oth) const{return x*oth.x+y*oth.y;}//点乘
	double operator%(const point&oth) const{return x*oth.y-y*oth.x;}//叉乘
}a[N];
int cnt;
struct line{
	point st,ed;
	void init(){st.init();ed.init();}
	double len(){return (ed-st).len();}
};
point Point_Projection(point p,line s){//一个点在一条线的投影点
	double k=((p-s.st)*(s.ed-s.st))/((s.ed-s.st)*(s.ed-s.st));
	return s.st+(s.ed-s.st)*k;
}
point Point_Reflection(point p,line s){//一个点关于一条线的对称点
	point p1=Point_Projection(p,s);
	return point{p1.x*2-p.x,p1.y*2-p.y};
}
int Point_OnWhichSide(point p,line s){//判断一个点在向量的哪一侧 (1:left 0:on line -1:right)
	return sgn((s.ed-s.st)%(p-s.st));
}
bool Point_OnLine(point p,line s){//判断一个点是否在一条直线上
	return sgn((s.ed-s.st)%(p-s.st))==0;
}
bool Point_OnSeg(point p,line s){//判断一个点是否在一条线段上
	return Point_OnLine(p,s)&&(sgn((p-s.st)*(p-s.ed))<=0);
}
bool Line_Parallel(line s1,line s2){//判断两条直线是否平行或重合
	return sgn((s1.ed-s1.st)%(s2.ed-s2.st))==0;
}
bool cmp(const point&x,const point&y){
	if(sgn(x.x-y.x)==0)return sgn(x.y-y.y)<0;
	return sgn(x.x-y.x)<0;
}
point sta[N];
int top;
int main(){
	int n;
	cin>>n;
	double x,y,r;
	cin>>x>>y>>r;
	x-=2*r,y-=2*r;
	double len=hypot(x,y)/2;
	double phi=atan(x/y);
	for(int i=1;i<=n;i++){
		double tx,ty,theta;
		cin>>tx>>ty>>theta;
		double dx=len*cos(theta+phi);
		double dy=len*sin(theta+phi);
		a[++cnt]={tx+dx,ty+dy};a[++cnt]={tx-dx,ty-dy};
		dx=len*cos(theta-phi);
		dy=len*sin(theta-phi);
		a[++cnt]={tx+dx,ty+dy};a[++cnt]={tx-dx,ty-dy};
	}
	sort(a+1,a+cnt+1,cmp);
	sta[++top]=a[1];sta[++top]=a[2];
	for(int i=3;i<=cnt;i++){
		while(top>1&&Point_OnWhichSide(a[i],line{sta[top-1],sta[top]})<=0)top--;
		sta[++top]=a[i];
	}
	int tmp=top;
	for(int i=cnt-1;i>=1;i--){
		while(top>tmp&&Point_OnWhichSide(a[i],line{sta[top-1],sta[top]})<=0)top--;
		sta[++top]=a[i];
	}
	double ans=pi*r*2;
	for(int i=1;i<=top-1;i++){ans+=line{sta[i],sta[i+1]}.len();}
	printf("%.2lf",ans);
}