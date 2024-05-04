#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n;
struct node{int x,y,z;}a[N];
double abss(double x){return x>0?x:-x;}
double w(int u,int v){return sqrt((a[u].x-a[v].x)*(a[u].x-a[v].x)+(a[u].y-a[v].y)*(a[u].y-a[v].y));}
double f(int u,int v,double mid){return abss(a[u].z-a[v].z)-mid*w(u,v);}
//u->v:|a[u].z-a[v].z|-mid*dis(u,v)
bool vis[N];
double dis[N];
bool check(double mid){
    for(int i=1;i<=n;i++)dis[i]=1e9,vis[i]=false;
	dis[1]=0;
	int tot=0;
	double ans=0;
	while(tot!=n){
		int Min=1e9,u=1;
		for(int i=1;i<=n;i++)if(!vis[i]&&dis[i]<Min)Min=dis[i],u=i;
		vis[u]=true;
		tot++;
		ans+=dis[u];
		for(int v=1;v<=n;v++){
			if(v==u)continue;
			if(dis[v]>f(u,v,mid))dis[v]=f(u,v,mid);
		}
	}
    return ans<0;
}
int main(){
    scanf("%d",&n);
    while(n){
        for(int i=1;i<=n;i++)scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
        double l=0,r=10000;
        for(int i=1;i<=30;i++){
            double mid=(l+r)/2;
            if(check(mid))r=mid;
            else l=mid;
        }
        printf("%.3lf\n",l);
        scanf("%d",&n);
    }
    
    return 0;
}