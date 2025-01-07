#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int INF=1e18;
int n,m,k,d;
struct node{
	int x,y,z;
}q[N];
int ans;
bool vis[N];
void dfs(int now,int sum){
	if(sum>k) return;
	if(now==n+1){
		int tmp=0;
		for(int i=1;i<=n;i++) tmp-=vis[i]*d;
		for(int i=1;i<=m;i++) {
			bool flag=true;
			for(int j=q[i].x-q[i].y+1;j<=q[i].x;j++) {
				if(!vis[j]) {flag=false;break;}
			}
			if(flag) tmp+=q[i].z;
		}
		ans=max(ans,tmp);
		return;
	}
	if(sum<k){
		vis[now]=true;
		dfs(now+1,sum+1);
	}
	vis[now]=false;
	dfs(now+1,0);
}
void solve(){
	ans=-INF;
	cin>>n>>m>>k>>d;
	for(int i=1;i<=m;i++) cin>>q[i].x>>q[i].y>>q[i].z;
	dfs(1,0);
	cout<<ans<<"\n";
}
signed main(){
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
	int c,T;
	cin>>c>>T;
	while(T-- )solve();
}


/*

全打暴力算了。

# T1

我们发现，T1的部分分给的非常多。

$ m\le 1$ 的点无脑过， $m\le 2$ 可能还要在思考一下。

对于一个字符串 $s$，字典序本身就大于他的不用管，考虑如何移动小于他的。

这个想一想就知道了。

-------------

直接暴力，由于我们想要当前的字典序最小，其他的最大，所以我们只需要把当前的从小到大排序，把其他的从大到小排序，然后判断就行了。

时间复杂度 $O(n^3\log n)$。

正解我个人认为应该是把 `sort` 改成基数排序，这样就能消掉一些复杂度，但不知道能不能过。而且我也不会写。

估分：[70,80]，不知道会不会被卡常……



# T2

对于 1，2 两个点，直接 dfs ，时间复杂度 $O(3^nm)$。

对于 3，4 两个点，由于只有赋值操作，所以每个变量的初值一定是他最后被赋予的值。

因此直接统计最后有几个 `U` 就行了。

暴力打挂了……

哦，把 `==` 打成 `=` 了

看了下 5，6 两个点，觉得有点像并查集维护一下就行了，但写出锅了

# T3

也没有思路。

10分跑路


# T4

什么鬼东西？

为什么同一天还会有多场挑战啊?

这给我整不会了，连贪心过样例都过不了，做个锤子。

这部分分也少的可怜，暴力DFS只有8分。

-------------------

估分：80+40+10+8=138

*/