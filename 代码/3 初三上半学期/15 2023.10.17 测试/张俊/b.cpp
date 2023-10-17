#include<bits/stdc++.h>
using namespace std;
const int N=55;
int n,m;
bool f[N][N];
vector<vector<long long> >v;
bool vis[N];
vector<long long> tmp;
vector<long long> tmp2;
int lim;
void dfs1(int x){
	if(x>lim) {
		long long now=0;
		for(int i=1;i<=n;i++) if(vis[i])now+=pow(2,i-1);
		int sum=0;
		int siz=tmp.size();
		for(int i=1;i<siz-1;i++) {
			int flag1=( f[tmp[i-1]][tmp[i]] && (!f[tmp[i]][tmp[i+1]]) );
			int flag2=( (!f[tmp[i-1]][tmp[i]]) && f[tmp[i]][tmp[i+1]] );
			if(flag1||flag2)sum++;
		}
		if(sum>1) return;
		tmp2=tmp;
		tmp2.push_back(sum);
		tmp2.push_back(now);
		v.push_back(tmp2);
		return;
	}
	for(int i=1;i<=n;i++) {
		if(!vis[i]){
			vis[i]=1;
			tmp.push_back(i);
			dfs1(x+1);
			tmp.pop_back();
			vis[i]=0;
		}
	}
	return;
}

void dfs2(int x){
	if(x>n-lim) {
		long long now=0;
		for(int i=1;i<=n;i++) if(vis[i])now+=pow(2,i-1);
		now--;
		int sum=0;
		int siz1=tmp.size();
				
		for(int i=1;i<siz1-1;i++) {
			int flag1=( f[tmp[i-1]][tmp[i]] && (!f[tmp[i]][tmp[i+1]]) );
			int flag2=( (!f[tmp[i-1]][tmp[i]]) && f[tmp[i]][tmp[i+1]] );
			if(flag1||flag2)sum++;
		}
		if(sum>1) return;
		int siz=v.size();
		for(int i=0;i<siz;i++){
			int SIZ=v[i].size();
			int l=v[i][SIZ-1];
			if((now&l)==0) {
				int s=v[i][SIZ-3];
				int ss;
				if(SIZ<=3) ss=s;
				else ss=v[i][SIZ-4];
				int t=tmp[0];
				int tt=tmp[1];
				int flag1=(f[ss][s]&&(!f[s][t]));
				int flag2=((!f[ss][s])&&f[s][t]);
				
				sum+=v[i][SIZ-2];
				if(flag1||flag2) sum++;
				
				flag1=(f[s][t]&&(!f[t][tt]));
				flag2=((!f[s][t])&&f[t][tt]);
				if(flag1||flag2) sum++;
				if(sum<=1){
					for(int j=0;j<SIZ-2;j++) cout<<v[i][j]<<" ";
					for(int j=0;j<siz1;j++) cout<<tmp[j]<<" ";
					exit(0);
				}
			}
		}
		return;
	}
	for(int i=1;i<=n;i++) {
		if(!vis[i]){
			vis[i]=1;
			tmp.push_back(i);
			dfs2(x+1);
			tmp.pop_back();
			vis[i]=0;
		}
	}
	return;
}
int main(){
	cin>>n>>m;
	if(n==2){
		cout<<"1 2";
		return 0;
	}
	lim=n/2;
	for(int i=1;i<=n;i++) f[i][i]=1;
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		f[u][v]=1;
		f[v][u]=1;
	}
	tmp.push_back(1);
	vis[1]=1;
	dfs1(2);
	tmp.clear();
	dfs2(1);
	return 0;
}