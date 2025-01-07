#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,INF=1e9;
struct node{
	int v,w,nex;
}a[N];
int first[N],cnt;
void add(int u,int v,int w) {
	a[++cnt]={v,w,first[u]};
	first[u]=cnt;
}
int n,m;
int dis1[N],dis2[N];
int pre[N];
void solve(int s,int t){
	for(int i=1;i<=n;i++) {dis1[i]=INF,dis2[i]=INF;}

	queue<int> q;
	dis1[s]=0;
	q.push(s);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=first[now];i;i=a[i].nex){
			int v=a[i].v;
			if(dis1[v]>dis1[now]+1) {
				dis1[v]=dis1[now]+1;
				q.push(v);
			}
		}
	}
	dis2[t]=0;
	q.push(t);
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=first[now];i;i=a[i].nex){
			int v=a[i].v;
			if(dis2[v]>dis2[now]+1) {
				dis2[v]=dis2[now]+1;
				q.push(v);
			}
		}
	}

	q.push(s);
	pre[s]=n+1;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=first[now];i;i=a[i].nex){
			if(a[i].w) continue;
			int v=a[i].v;
			if(!pre[v]) {pre[v]=now;q.push(v);}
		}
	}

	if(pre[t]) {
		cout<<"0\n";
		vector<int>tmp;
		int now=t;
		while(true){
			tmp.push_back(now);
			if(now==s) break;
			now=pre[now];
		}
		cout<<tmp.size()<<"\n";
		for(int v:tmp)cout<<v-1<<" ";
		return;
	}

	vector<int> vec;
	int Min=INF;
	for(int i=1;i<=n;i++)if(pre[i])Min=min(Min,dis2[i]);
	for(int i=1;i<=n;i++)if(pre[i]&&dis2[i]==Min) vec.push_back(i);
 	vector<int> ans;
	while(true) {
		pair<int,int> pii={INF,INF};  //�ҵ���һ������Ž�
		for(int now:vec) {
			for(int i=first[now];i;i=a[i].nex){
				int v=a[i].v;
				if(dis2[v]>dis2[now]) continue;
				if(pre[v]&&dis1[pre[v]]<dis1[now]) continue;
				pii=min(pii,{dis2[v],a[i].w});
			}
		}
		ans.push_back(pii.second);
		vector<int> nex_vec;	//��һ��ĵ�
		for(int now:vec) {
			for(int i=first[now];i;i=a[i].nex){
				int v=a[i].v;
				if(dis2[v]>dis2[now]) continue;
				if(pre[v]&&dis1[pre[v]]<dis1[now]) continue;
				if(dis2[v]==pii.first && a[i].w==pii.second) {
					nex_vec.push_back(v);
					pre[v]=now;
				}
			}
		}

		for(int now:nex_vec) {
			if(now==t) {
				for(int i:ans) cout<<i;
				cout<<"\n";
				vector<int> tmp;
				while(true) {
					tmp.push_back(now);
					if(now==s) break;
					now=pre[now];
				}
				cout<<tmp.size()<<"\n";
				for(int i:tmp) cout<<i-1<<" ";
				return;
			}
		}
		vec=nex_vec;
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);

	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		u++,v++;
		add(u,v,w);
		add(v,u,w);
	}
	int s=n,t=1;
	solve(s,t);
}
