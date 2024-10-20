#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,M=700;
const double INF=1e18;
int d[N],m[N];
int sum[N];
int belong[N],l[N],r[N];
int sta[M][M],top[M];
double slope(int i,int j){
    if(m[i]<=m[j])return INF;
    return min(INF,1.0*(sum[j]-sum[i])/(m[j]-m[i]));
}
bool check(int x,int y,int i){
    double k1=slope(x,y),k2=slope(y,i);
    if(k2>=INF)return false;
    return k1<=k2;
}
void build(int k){
    top[k]=0;
    for(int i=l[k];i<=r[k];i++){
        while(top[k]>1&&check(sta[k][top[k]-1],sta[k][top[k]],i))top[k]--;
        if(!top[k]||(top[k]&&slope(sta[k][top[k]],i)<INF))sta[k][++top[k]]=i;
    }
    sta[k][top[k]+1]=0;
}
int lazy[M];
int ask(int k,int val){return sum[k]+lazy[belong[k]]+m[k]*val;}
int query(int k,int val){
	int l=1,r=top[k];
	int ans=INF;
	while(l<=r){
		int mid=(l+r)>>1;
		ans=min(ans,ask(sta[k][mid],val));
		if(ask(sta[k][mid],val)>ask(sta[k][mid+1],val))l=mid+1;
		else if(ask(sta[k][mid],val)>ask(sta[k][mid-1],val))r=mid-1;
		else l=mid+1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>d[i],sum[i]=sum[i-1]+d[i];
	for(int i=1;i<=n;i++)cin>>m[i];
	int block=650;
	int tot=n/block+(n%block!=0);
	for(int i=1;i<=tot;i++)l[i]=r[i-1]+1,r[i]=i*block;
	r[tot]=n;
	for(int i=1;i<=tot;i++)for(int j=l[i];j<=r[i];j++)belong[j]=i;
	for(int i=1;i<=tot;i++)build(i);
	while(q--){
		int opt,p,f,v;
		cin>>opt>>p>>f>>v;
		if(opt==1){
			for(int i=belong[p]+1;i<=tot;i++)lazy[i]+=f-d[p];
			for(int i=p;i<=r[belong[p]];i++)sum[i]+=f-d[p];
			d[p]=f;
			build(belong[p]);
		}
		else m[p]=f,build(belong[p]);
		int ans=INF;
		for(int i=1;i<=tot;i++)ans=min(ans,query(i,v));
		cout<<ans<<"\n";
	}
}