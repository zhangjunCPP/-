#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n;
struct node{
	int v,nex;
}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int dep[N];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(int i=first[u];i;i=a[i].nex){
		int v=a[i].v;
		if(v==fa)continue;
		dfs(v,u);
	}
}
int p[N];
int vis[N];
int deg[N];
int dis[25][25];
int val[25];
bool bf_flag;
bool check(int x,int y){
	if(x%3==0||y%3==0)return true;
	if((x+y)%3==0)return true;
	return false;
}
void dfs(int k,int sum0,int sum1,int sum2){
	if(k>n){
		if(sum0||sum1||sum2||bf_flag)return;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(dis[i][j]==3&&!check(val[i],val[j]))return;
			}
		}
		cout<<"Yes\n";
		bf_flag=true;
		int val1=1,val2=2,val0=3;
		for(int i=1;i<=n;i++){
			if(val[i]==1)cout<<val1<<" ",val1+=3;
			if(val[i]==2)cout<<val2<<" ",val2+=3;
			if(val[i]==0)cout<<val0<<" ",val0+=3;
		}
		cout<<"\n";
		return;
	}
	if(sum0){val[k]=0;dfs(k+1,sum0-1,sum1,sum2);}
	if(sum1){val[k]=1;dfs(k+1,sum0,sum1-1,sum2);}
	if(sum2){val[k]=2;dfs(k+1,sum0,sum1,sum2-1);}
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)first[i]=0,dep[i]=0,deg[i]=0;
	cnt=0;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);add(v,u);
	}
	if(n<=20){
		bf_flag=false;
		for(int u=1;u<=n;u++){
			for(int v=1;v<=n;v++)dis[u][v]=1000;
			dis[u][u]=0;
		}
		for(int u=1;u<=n;u++){
			for(int i=first[u];i;i=a[i].nex){
				int v=a[i].v;
				dis[u][v]=1;
			}
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		int p_0=0,p_1=0,p_2=0;
		for(int i=1;i<=n;i++){
			if(i%3==1)p_1++;
			else if(i%3==2)p_2++;
			else p_0++;
		}
		dfs(1,p_0,p_1,p_2);
		if(!bf_flag)cout<<"No\n";
		return;
	}
	dfs(1,0);
	int Maxdep=-1;
	int p_0=0,p_1=0,p_2=0;
	int p_0_last,p_1_last,p_2_last;
	for(int i=1;i<=n;i++){
		if(i%3==1)p_1++,p_1_last=i;
		else if(i%3==2)p_2++,p_2_last=i;
		else p_0++,p_0_last=i;
		Maxdep=max(Maxdep,dep[i]);
	}
	if((Maxdep==3&&deg[1]==1)||Maxdep<=2){cout<<"Yes\n";for(int i=1;i<=n;i++)cout<<i<<" ";return;}
	int tmp_p_1=p_1,tmp_p_2=p_2;
	int val1=1,val2=p_2_last;
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++){
		if(dep[i]&1){
			p[i]=val1;
			val1+=3;
			p_1--;
			if(p_1==0)val1=3;
		}
		else{
			p[i]=val2;
			val2-=3;
			p_2--;
			if(p_2==0)val2=p_0_last;
		}
		vis[p[i]]++;
	}
	bool flag=true;
	for(int i=1;i<=n;i++)if(vis[i]!=1){flag=false;break;}
	if(flag){cout<<"Yes\n";for(int i=1;i<=n;i++)cout<<p[i]<<" ";cout<<"\n";return;}
	val1=2,val2=p_1_last;
	p_1=tmp_p_2,p_2=tmp_p_1;
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++){
		if(dep[i]&1){
			p[i]=val1;
			val1+=3;
			p_1--;
			if(p_1==0)val1=3;
		}
		else{
			p[i]=val2;
			val2-=3;
			p_2--;
			if(p_2==0)val2=p_0_last;
		}
		vis[p[i]]++;
	}
	flag=true;
	for(int i=1;i<=n;i++)if(vis[i]!=1){flag=false;break;}
	if(flag){cout<<"Yes\n";for(int i=1;i<=n;i++)cout<<p[i]<<" ";cout<<"\n";return;}
	cout<<"No\n";
}
signed main(){
	// freopen("ex_tree.in","r",stdin);
	// freopen("ex_tree.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}