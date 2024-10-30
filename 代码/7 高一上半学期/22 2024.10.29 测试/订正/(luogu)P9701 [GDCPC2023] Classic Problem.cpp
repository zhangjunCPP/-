#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e18;
int tmp[N],tot;
struct node{
	int u,v,w;
}a[N];
struct node2{
	int l,r;
	node2(int _l=0,int _r=0):l(_l),r(_r){}
	bool operator<(const node2&oth)const{return l<oth.l;}
}q[N];
map<pair<int,int>,int>mp;
set<int> st[N];
int fa[N];
int find(int x){
	if(fa[x]!=x)fa[x]=find(fa[x]);
	return fa[x];
}
pair<int,int> Min[N];
int pre[N],nex[N];
void solve(){
	int n,m;
	cin>>n>>m;
	mp.clear();
	for(int i=1;i<=m*4;i++)st[i].clear();
	tot=0;
	for(int i=1;i<=m;i++){
		cin>>a[i].u>>a[i].v>>a[i].w;
		tmp[++tot]=a[i].u;
		tmp[++tot]=a[i].v;
	}
	sort(tmp+1,tmp+tot+1);
	tot=unique(tmp+1,tmp+tot+1)-tmp-1;
	tmp[0]=0,tmp[tot+1]=n+1;
	n=0;
	for(int i=1;i<=tot;i++)q[++n]={tmp[i],tmp[i]};
	int ans=0;
	for(int i=0;i<=tot;i++){
		if(tmp[i]+1!=tmp[i+1]){
			q[++n]={tmp[i]+1,tmp[i+1]-1};
			ans+=tmp[i+1]-tmp[i]-2;
		}
	}
	sort(q+1,q+n+1);
	for(int i=1;i<=m;i++){
		int u=a[i].u,v=a[i].v,w=a[i].w;
		u=lower_bound(q+1,q+n+1,node2(u,u))-q;
		v=lower_bound(q+1,q+n+1,node2(v,v))-q;
		if(u>v)swap(u,v);
		st[u].insert(v);
		st[v].insert(u);
		mp[{u,v}]=mp[{v,u}]=w;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	while(true){
		bool flag=false;
		for(int i=1;i<=n;i++)if(find(i)!=find(1)){flag=true;break;}
		if(!flag)break;
		for(int i=1;i<=n;i++)Min[i]={INF,-1};
		for(int u=1;u<=n;u++){
			for(int v:st[u]){
				int fx=find(u),fy=find(v);
				if(fx==fy)continue;
				Min[fx]=min(Min[fx],{mp[{u,v}],fy});
			}
		}
		for(int i=1,j=1;i<=n;){
			while(j<n&&find(j+1)==find(i))j++;
			for(int l=i;l<=j;l++)pre[l]=i-1,nex[l]=j+1;
			j++;
			i=j;
		}
		for(int u=1;u<=n;u++){
			int v=u;
			int fx=find(u);
			while(v>=1&&(fx==find(v)||st[u].find(v)!=st[u].end())){
				if(fx==find(v))v=pre[v];
				else v--;
			}
			if(v)Min[fx]=min(Min[fx],{q[u].l-q[v].r,find(v)});

			v=u;
			while(v<=n&&(fx==find(v)||st[u].find(v)!=st[u].end())){
				if(fx==find(v))v=nex[v];
				else v++;
			}
			if(v<=n)Min[fx]=min(Min[fx],{q[v].l-q[u].r,find(v)});
		}
		for(int i=1;i<=n;i++){
			if(fa[i]==i){
				int fx=find(i);
				int fy=find(Min[i].second);
				if(fx!=fy){
					fa[fx]=fy;
					ans+=Min[i].first;
				}
			}
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}