/*
���ȣ���ĿҪ�����ǽ�n��Ϊ���ɸ� $k$ �������ĺͣ���ʵ���ǽ� $n$ ��Ϊ���ɸ� $k$ ��**��**�����ĺ͡�

���֣������ [P3403��¥��](https://www.luogu.com.cn/problem/P3403)��

���ǣ���Ҫ�� $k$ �����������ڵ����������������������Ҫ�������ۡ�

1. $k$ û����������ֻ��1��
2. $k$ ֻ��1�������������Լ�����ʱ��$n$ ҪΪ $k$ �ı�����
3. $k$ ��������������
   ��Ҫ�������ж� $ax+by=n$ �Ƿ��н⡣����ǱȽϺ��жϵġ�
   ���ҽ��� $n\times b^{-1} (\mod a\ ) \ \times b \le n$
4. $k$ �����������ϵ���������ֱ�Ӱ���[P3403��¥��](https://www.luogu.com.cn/problem/P3403)�����ɡ�

ע�⣬���� $k$ ��ȡֵֻ��50�֣��� $t\le 10^4$��˵���кܶ��ظ��� $k$ �����������Ҫ����

*/
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=3.3e7+10,M=5e6+10;
map<ll,vector<pair<ll,int> > > mp;
bool ans[M];

int prime[M],vis[N],tot;
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<N;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) break;
		}
	}
}

ll qpow(ll x,ll y,ll mod){
	ll ans=1;
	while(y) {
		if(y&1) ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}

ll a[M];
ll dis[M];
bool vis2[M];
queue<ll> q;
signed main(){
	init();

	int T;
	cin>>T;
	for(int i=1;i<=T;i++) {
		ll x,y;
		cin>>x>>y;
		mp[y].push_back({x,i});
	}
	for(auto now:mp) {
		ll k=now.first;
		if(k==1) continue;

		ll sum=0;
		ll tmp=k;		
		
		for(int i=1;i<=tot&&prime[i]*prime[i]<=tmp;i++){
			if(tmp%prime[i]==0){
				sum++;
				a[sum]=prime[i];
				while(tmp%prime[i]==0) tmp/=prime[i];
			}
		} 

		if(tmp>1) sum++,a[sum]=tmp;
		if(sum==1) {
			for(auto it:now.second){
				if(it.first%k==0) ans[it.second]=true;
				else ans[it.second]=false;
			}
		}
		else if(sum==2) {
			for(auto it:now.second){
				ll n=it.first;
				if(n%a[1]==0||n%a[2]==0) {ans[it.second]=true;continue;}
				if(( (n%a[1]) * qpow(a[2],a[1]-2,a[1])%a[1] )%a[1]*a[2]<=n){ans[it.second]=true;continue;}
				ans[it.second]=false;
			}
		}
		else {
			// �� a[1] ��Ϊģ��
			for(int i=0;i<a[1];i++) {
				vis2[i]=false;
				dis[i]=1e18+10;
			}
			dis[0]=0;
			vis2[0]=true;
			q.push(0);
			while(!q.empty()){
				int u=q.front();
				q.pop();
				vis2[u]=false;
				for(int i=2;i<=sum;i++) {
					if(dis[(u+a[i])%a[1]]>dis[u]+a[i]) {
						dis[(u+a[i])%a[1]]=dis[u]+a[i];
						if(!vis2[(u+a[i])%a[1]]) q.push((u+a[i])%a[1]),vis2[(u+a[i])%a[1]]=true;
					}
				}
			}
			for(auto it:now.second){
				int n=it.first;
				if(dis[n%a[1]]<=n) ans[it.second]=true;
				else ans[it.second]=false;
			}
		}
	}
	for(int i=1;i<=T;i++) {
		if(ans[i]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
