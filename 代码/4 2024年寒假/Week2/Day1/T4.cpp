#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=6e5+10;
const ull p=131,P[2]={13,17};//对于左右括号要用不同的底数
ull pw[N];
void init(){
	pw[0]=p;
	for(int i=1;i<=20;i++) pw[i]=pw[i-1]*pw[i-1];
}
int tot;
int val[N];//字典树的原字符
int tree[N][2];
int fa[N][20];
ull Hash[N][20];
int add(int u,int ch){
	if(!tree[u][ch]){
		tree[u][ch]=++tot;
		fa[tot][0]=u;
		val[tot]=ch;
		Hash[tot][0]=P[ch];
		for(int i=1;i<20;i++){
			fa[tot][i]=fa[fa[tot][i-1]][i-1];
			Hash[tot][i]=Hash[tot][i-1]*pw[i-1]+Hash[fa[tot][i-1]][i-1];
		}
	}
	return tree[u][ch];
}
bool check(int x,int y){
	for(int i=19;i>=0;i--)if(Hash[x][i]==Hash[y][i]) x=fa[x][i],y=fa[y][i];
	return val[x]<val[y];
}
//将)记为+1，(记为-1，那么我们就能很容易地知道每个(匹配的（下一个）位置。
int nex[N],pos[N+N];
int dp[N];
string solve(int x){
	string ans;
	while(x>1) {
		ans.push_back(val[x]+'(');
		x=fa[x][0];
	}
	return ans;
}
int main(){
	init();
	string s;
	cin>>s;
	int n=s.size();
	memset(pos,-1,sizeof pos);
	pos[N]=n;
	int tmp=0;
	for(int i=n-1;i>=0;i--){
		tmp+=s[i]==')'?1:-1;
		if(s[i]=='(') nex[i]=pos[tmp+N];
		else nex[i]=-1;
		pos[tmp+N]=i;
	}
	dp[n]=++tot;val[tot]=-1;//根节点
	for(int i=n-1;i>=0;i--){
		int ch=s[i]-'(';
		if(nex[i]==-1)dp[i]=add(dp[i+1],ch);
		else {
			int x=add(dp[i+1],ch),y=dp[nex[i]];
			dp[i]=check(x,y)?x:y;
		}
	}
	cout<<solve(dp[0]);
}
