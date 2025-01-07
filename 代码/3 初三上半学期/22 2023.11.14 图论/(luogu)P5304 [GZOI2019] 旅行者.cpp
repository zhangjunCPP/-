/*
��������Ϊ�����㼯A,B
s��A�е����е���һ����ȨΪ0�ıߡ�
B�е����е���t��һ����ȨΪ0�ıߡ�
Ȼ��s��t�����·����Ҫ��Ĵ𰸡�
���Ƿ��֣�����Ȥ��������һ����ͬ��
Ҳ����˵�����ǵĶ�����λ������һλ��ͬ
��ô���Ǿ�����һ�� O(Tnlognlogk) ��������
��Ȼ��������ʱ�临�Ӷȣ������ܹ�

��ⲻ��գ�����ʹ����
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct node{
	int v,w,nex;
}a[N],tmp1[N];
int first[N],cnt,tmp2[N];
void add(int u,int v,int w){
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}

void init(){
	memset(first,0,sizeof(first));
	cnt=0;
}
int dis[N];
bool vis[N];
struct node2{
	int id,w;
	bool operator <(const node2 &b)const {
		return w>b.w;
	}
};
int dij(int s,int t) {
	priority_queue<node2> q;
	memset(dis,0x3f,sizeof(dis));
	memset(vis,false,sizeof vis);
	dis[s]=0;
	q.push({s,0});
	while(!q.empty()) {
		int u=q.top().id;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=first[u];i;i=a[i].nex){
			int v=a[i].v;
			if(dis[v]>dis[u]+a[i].w){
				dis[v]=dis[u]+a[i].w;
				q.push({v,dis[v]});
			}
		}
	}
	return dis[t];
}
int b[N];
void solve(){
	init();
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) {
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
	}
	for(int i=1;i<=k;i++) cin>>b[i];
	int ans=1e18;
	for(int i=0;(1<<i)<=k;i++) {
		memcpy(tmp1,a,sizeof a);
		memcpy(tmp2,first,sizeof first);

		int s=n*2+1,t=n*2+2;
		for(int j=1;j<=k;j++) {
			if((j>>i)&1) add(s,b[j],0);
			else add(b[j],t,0);
		}
		ans=min(ans,dij(s,t));
		memcpy(a,tmp1,sizeof tmp1);
		memcpy(first,tmp2,sizeof tmp2);
		for(int j=1;j<=k;j++) {
			if((j>>i)&1) add(b[j],t,0);
			else add(s,b[j],0);
		}
		ans=min(ans,dij(s,t));
		memcpy(a,tmp1,sizeof tmp1);
		memcpy(first,tmp2,sizeof tmp2);
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--) solve();
}
