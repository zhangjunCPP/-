#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=2e4+10,M=1e3+10;
int n,m,q,B,cur[N],rk[N],high[N];
char a[N][M];
int nex[N][M],b[M][N];
bitset<N>s;
struct ques{
	int l,r,id;
	bool operator < (const ques &a)const{
		return l/B!=a.l/B?l/B<a.l/B:r<a.r;
	}
}o[N];
vector<int>pos[M];
int solve(){
	int siz=s.count();
	if(!siz)return 0;
	for(int i=0;i<=m;i++)pos[i].clear();
	static int id[M];
	int len=0;
	for(int p=s._Find_first();p<s.size();p=s._Find_next(p)){
		if(len>m+2)break;
		id[len++]=cur[p];
	}
	int mx=-1,p=-1;
	for(int i=0;i<len;i++){
		int val=siz-i+high[id[i]];
		if(val>=mx)mx=val,p=i;
	}
	if([&](){
		if(p)return 0;
		if(nex[id[p]][high[id[p]]]!=-1)return 0;
		for(int i=p+1;i<len;i++){
			if(high[id[p]]-1+i-p==high[id[i]]&&nex[id[i]][high[id[i]]]!=-1)return 0;
		}
		return 1;
	}())return mx-1;
	int ret=0;
	for(int i=0;i<=p;i++){
		ret++;
		pos[high[id[i]]].push_back(id[i]);
	}
	for(int i=high[id[p]],cur=high[id[p]];i>=0;i--){
		if(i<=cur){
			nth_element(pos[i].begin(),pos[i].begin()+min<int>(cur-i,pos[i].size()),pos[i].end(),
				[&](int x,int y){return b[i][x]>b[i][y];});
		}
		for(int x:pos[i]){
			if(i>cur){
				if(ret==1&&cur+1==i&&nex[x][i]==-1)return mx;
				return mx+1;
			}else if(i==cur){
				cur--;
				int j=nex[x][i];
				if(j>=0)pos[j].push_back(x);
				else ret--;
			}else cur--,ret--;
		}
	}
	return mx;
}
int ans[N];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	if(B=n/sqrt(q),B<1)B=1;
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]);
		reverse(a[i],a[i]+m);
		high[i]=-1;
		for(int j=0,las=-1;j<m;j++){
			if(a[i][j]=='1'){
				high[i]=j,nex[i][j]=las,las=j;
			}
		}
	}
	iota(cur,cur+1+n,0);
	for(int k=0;k<m;k++){
		int t=0;
		for(int i=1;i<=n;i++){
			if(a[cur[i]][k]=='0')b[k][cur[i]]=++t;
		}
		for(int i=1;i<=n;i++){
			if(a[cur[i]][k]=='1')b[k][cur[i]]=++t;
		}
		for(int i=1;i<=n;i++)cur[b[k][i]]=i;
	}
	for(int i=1;i<=q;i++){
		scanf("%d%d",&o[i].l,&o[i].r),o[i].id=i;
	}
	sort(o+1,o+1+q);
	for(int i=1,l=1,r=0;i<=q;i++){
		for(;r<o[i].r;)if(~high[++r])s.flip(b[m-1][r]);
		for(;l>o[i].l;)if(~high[--l])s.flip(b[m-1][l]);
		for(;r>o[i].r;)if(~high[r])s.flip(b[m-1][r--]);else r--;
		for(;l<o[i].l;)if(~high[l])s.flip(b[m-1][l++]);else l++;
		ans[o[i].id]=solve();
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif