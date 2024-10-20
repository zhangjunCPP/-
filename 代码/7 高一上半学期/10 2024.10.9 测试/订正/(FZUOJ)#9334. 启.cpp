#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
bool vis[N];
int prime[N],prime_tot;
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i])prime[++prime_tot]=i;
		for(int j=1;j<=prime_tot&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
vector<pair<int,int>> G[N];
int col[N];
int cnt[2];
int belong[N];
void dfs(int u,int color,int tot){
	col[u]=color;
	belong[u]=tot;
	cnt[color-1]++;
	for(auto it:G[u]){
		int v=it.first,opt=it.second;
		if(!col[v])dfs(v,opt?3-color:color,tot);
		else{
			int tmp=opt?3-color:color;
			if(col[v]!=tmp){cout<<"-1";exit(0);}
		}
	}
}
bitset<N>dp[1005];
int sum[N];
int num[N];
vector<int>q[N];
int ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	init();
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int opt,u,v;
		cin>>opt>>u>>v;
		G[u].push_back({v,opt});
		G[v].push_back({u,opt});
	}
	int tot=0;
	int sum_cnt=0;
	for(int i=1;i<=n;i++){
		if(col[i])continue;
		cnt[0]=cnt[1]=0;
		tot++; 
		dfs(i,1,tot);
		if(cnt[0]<cnt[1])swap(cnt[0],cnt[1]),ans[tot]=1;
		else ans[tot]=0;
		sum[cnt[0]-cnt[1]]++;
		q[cnt[0]-cnt[1]].push_back(tot);
		sum_cnt+=cnt[1];
	}
	//记每个连通块的代价为cnt[0]-cnt[1]。初始全选cnt[1]为黑点，此后，每往背包里加入一个数，就代表这个连通块换成了cnt[0]为黑点。
	//因此可以进行一个01背包，代表每个连通块交不交换
	//注意到其实代价相同的很多，因此我们可以一起处理，进行二进制分组做多重背包
	//这样做的正确性是因为每个连通块并不区分，我们只需要知道这种代价的连通块选了几个，然后我们随便从中选就可以了
	//为了方便，用桶记录。dp[i][j]表示对于代价前i小的连通块，是否能凑出j
	int id=0;
	dp[0][sum_cnt]=true;
	for(int i=1;i<=n;i++){
		if(!sum[i])continue;
		id++;
		dp[id]=dp[id-1];
		num[id]=i;
		int tmp=sum[i];
		for(int j=1;j<=tmp;j<<=1){
			dp[id]|=(dp[id]<<(i*j));
			tmp-=j;
		}
		if(tmp)dp[id]|=(dp[id]<<(i*tmp));
	}
	int pos=n/2;
	while(!dp[id][pos])pos--;
	int ans_sum=1;
	while(ans_sum*ans_sum-ans_sum+2<max(pos,n-pos))ans_sum++;
	vector<pair<int,int>> line;
	line.push_back({prime[1],0});
	line.push_back({prime[1],prime[1]});
	for(int i=1;i<=ans_sum;i++){
		for(int j=1;j<=ans_sum;j++){
			if(i==j)continue;
			line.push_back({prime[i],prime[j]});
		}
	}
	cout<<ans_sum+1<<"\n";
	//凑出的数为pos
	for(int i=id;i;i--){
		int tmp=num[i];
		for(int j=0;j<=sum[tmp]&&tmp*j<=pos;j++){
			if(dp[i-1][pos-tmp*j]){
				pos-=tmp*j;
				for(int k=1;k<=j;k++){
					int x=q[tmp].back();q[tmp].pop_back();
					ans[x]^=1;
				}
				break;
			}
		}
	}
	int pos1=0,pos2=0;
	for(int i=1;i<=n;i++){
		if(ans[belong[i]]){//不交换
			if(col[i]==1)cout<<"0 "<<line[pos1].first<<" "<<line[pos1].second<<"\n",pos1++;
			else cout<<line[pos2].first<<" 0 "<<line[pos2].second<<"\n",pos2++;
		}
		else{//交换
			if(col[i]==2)cout<<"0 "<<line[pos1].first<<" "<<line[pos1].second<<"\n",pos1++;
			else cout<<line[pos2].first<<" 0 "<<line[pos2].second<<"\n",pos2++;
		}
	}
}