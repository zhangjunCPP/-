#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=5e18;
int n,q;
struct node{
	int w,h;
}a[N];
int l[N],r[N];
int calc(int x,int y){return (a[y].w-a[x].w)*(a[x].h+a[y].h);}
int tree[N];
int lowbit(int x){return x&(-x);}
void init(){for(int i=1;i<=n;i++)tree[i]=INF;}
void add(int x,int val){for(int i=x;i<=n;i+=lowbit(i))tree[i]=min(tree[i],val);}
int query(int x){
	int ans=INF;
	for(int i=x;i;i-=lowbit(i))ans=min(ans,tree[i]);
	return ans;
}
vector<pair<int,int>>V[N],Q[N];
int ans[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i].w>>a[i].h;
	stack<int> s;
	for(int i=1;i<=n;i++){
		while(!s.empty()&&a[s.top()].h>a[i].h)s.pop();
		if(s.empty())l[i]=0;
		else l[i]=s.top();
		s.push(i);
	}
	while(!s.empty())s.pop();
	for(int i=n;i;i--){
		while(!s.empty()&&a[s.top()].h>a[i].h)s.pop();
		if(s.empty())r[i]=0;
		else r[i]=s.top();
		s.push(i);
	}
	for(int i=1;i<=n;i++)if(l[i])V[l[i]].emplace_back(i,calc(l[i],i));
	for(int i=1;i<=n;i++)if(r[i])V[i].emplace_back(r[i],calc(i,r[i]));
	for(int i=1;i<=q;i++){
		int L,R;
		cin>>L>>R;
		Q[L].emplace_back(R,i);
	}
	init();
	for(int i=n;i;i--){
		for(auto it:V[i])add(it.first,it.second);
		for(auto it:Q[i])ans[it.second]=query(it.first);
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
}