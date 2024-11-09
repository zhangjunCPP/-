#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,q,id,k;
int last,a[500005];
int t[500005];
int num,mx,r[500005];
int sum,l[500005];
bool death[500005];
using pi=pair<int,int>;
priority_queue<pi,vector<pi>,greater<pi> >dl;
priority_queue<int>ld;
void ini(){
	last=sum=0;
	memset(death,0,sizeof(death));
	memset(r,0,sizeof(r));
	while(dl.size())dl.pop();
	while(ld.size())ld.pop();
	return;
}
int calc(int x,int y){
	x=t[x],y=t[y];
	// cout<<x<<' '<<y<<" "<<a[y]<<" "<<a[x]<<"\n";
	return ceil((a[y]-a[x])*1.0/(x-y));
}
void mymain(){
	cin>>q;
	for(int i=1;i<=n;++i)cin>>a[i],assert(a[i]>=0);
	num=0,mx=-1;
	for(int i=n;i;--i){
		if(a[i]<=mx)continue;
		t[++num]=i;
		mx=max(mx,a[i]);
	}
	for(int i=1;i<=num;++i){
		ld.push(i);
		l[i]=i-1,r[i]=i+1;
		if(i!=num)dl.push({calc(i,r[i]),i});
		else dl.push({3e18,i});
	}
	while(q--){
		cin>>k;
		if(id)k=(k^(last%(k+1)));
		sum+=k;
		while(dl.size() and dl.top().first<=sum){
			int x=dl.top().second;
			// cout<<dl.top().first<<' '<<x<<' '<<r[x]<<'\n';
			dl.pop();
			if(death[x])continue;
			death[r[x]]=1;
			r[x]=r[r[x]];
			if(r[x] and r[x]<=num){
				dl.push({calc(x,r[x]),x});
			}
		}
		while(ld.size() and death[ld.top()])ld.pop();
		int l=t[ld.top()];
		last=a[l]+sum*l;
		cout<<last<<'\n';
	}
	return;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>T>>n>>id;
	while(T--)ini(),mymain();
	return 0;
}