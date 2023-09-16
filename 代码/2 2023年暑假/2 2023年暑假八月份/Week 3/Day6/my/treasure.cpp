#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=30;
int n;
int a[N];
int MIN;
struct node{
	int sum1,sum2,sum3,t;
};
vector<node> v;
void dfs1(int x,int sum1,int sum2,int sum3,int t){
	if(x>n/2){
		v.push_back({sum1,sum2,sum3,t});
		return;
	}
	dfs1(x+1,sum1+a[x],sum2,sum3,t);
	dfs1(x+1,sum1,sum2+a[x],sum3,t+1*pow(3,x-1));
	dfs1(x+1,sum1,sum2,sum3+a[x],t+2*pow(3,x-1));
	return;
}
int ans=0x3f3f3f3f;
int ans1,ans2;
void dfs2(int x,int sum1,int sum2,int sum3,int t){
	if(x>n){
		for(node now:v){
			int tmp1=sum1+now.sum1;
			int tmp2=sum2+now.sum2;
			int tmp3=sum3+now.sum3;
			if(max({tmp1,tmp2,tmp3})-min({tmp1,tmp2,tmp3})<ans){
				ans=max({tmp1,tmp2,tmp3})-min({tmp1,tmp2,tmp3});
				ans1=now.t+t;
			}
		}
		return;
	}
	dfs2(x+1,sum1+a[x],sum2,sum3,t);
	dfs2(x+1,sum1,sum2+a[x],sum3,t+1*pow(3,x-1));
	dfs2(x+1,sum1,sum2,sum3+a[x],t+2*pow(3,x-1));
}
signed main(){
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	dfs1(1,0,0,0,0);
	dfs2(n/2+1,0,0,0,0);
	for(int i=1;i<=n;i++){
		cout<<ans1%3+1<<" ";
		ans1/=3;
	}
	return 0;
}

