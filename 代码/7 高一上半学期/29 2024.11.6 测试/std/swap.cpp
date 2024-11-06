#include<bits/stdc++.h>
using namespace std;
using i64=long long;
constexpr i64 mod=1000000007;
int W,n,p[1000010],val[1000010],L[1000010],R[1000010],stk[1000010],tp,deg[1000010];
bool flag[1000010];
vector<int>G[1000010];
namespace ds{
	int cnt[1000010];
	inline void ins(int p){
		for(;p<=n;p+=p&-p)cnt[p]++;
	}
	inline int ask(int p){
		int r=0;for(;p;p-=p&-p)r+=cnt[p];
		return r;
	}
}
int main(){
	cin>>n>>W;
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]),flag[i]=val[i]<=W/2;
	assert(1<=n&&n<=1000000);
	assert(1<=W&&W<=1000000000);
	for(int i=1;i<=n;i++)assert(1<=val[i]&&val[i]<=W);
	set<int>S;
	for(int i=1;i<=n;i++)S.insert(p[i]);
	assert(*begin(S)==1&&*rbegin(S)==n&&S.size()==n);
	for(int i=1;i<=n;i++){
		if(flag[p[i]]){
			L[i]=*(partition_point(stk+1,stk+tp+1,[&](int x){return val[p[x]]+val[p[i]]>W;})-1);
		}else{
			for(;tp&&val[p[stk[tp]]]<=val[p[i]];tp--);
			stk[++tp]=i;
		}
	}
	tp=0,stk[0]=n+1;
	for(int i=n;i>=1;i--){
		if(flag[p[i]]){
			R[i]=*(partition_point(stk+1,stk+tp+1,[&](int x){return val[p[x]]+val[p[i]]>W;})-1);
		}else{
			for(;tp&&val[p[stk[tp]]]<=val[p[i]];tp--);
			stk[++tp]=i;
		}
	}
	i64 ans=1;
	vector<int>perm;
	for(int i=1;i<=n;i++){
		if(!flag[p[i]])ds::ins(i);
		else perm.push_back(i);
	}
	sort(begin(perm),end(perm),[](int x,int y){
		return R[x]-L[x]<R[y]-L[y];
	});
	for(int u:perm){
		(ans*=ds::ask(R[u]-1)-ds::ask(L[u+1-1])+1)%=mod;
		ds::ins(u);
	}
	printf("%lld\n",ans);
	perm={};
	for(int i=1;i<=n;i++){
		if(!flag[p[i]])perm.push_back(i);
		else{
			if(L[i])G[L[i]].push_back(i);
			if(R[i]!=n+1)G[i].push_back(R[i]);
		}
	}
	for(int i=1;i<perm.size();i++)G[perm[i-1]].push_back(perm[i]);
	for(int i=1;i<=n;i++)for(int v:G[i])deg[v]++;
	struct CMP_{
		bool operator()(int x,int y)const{
			return p[x]>p[y];
		}
	};
	priority_queue<int,vector<int>,CMP_>q;
	for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
	for(;!q.empty();){
		int u=q.top();q.pop();
		printf("%d ",p[u]);
		for(int v:G[u])if(!--deg[v])q.push(v);
	}
	return 0;
}