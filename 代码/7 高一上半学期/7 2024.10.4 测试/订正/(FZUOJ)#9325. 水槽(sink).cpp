#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int a[N];
int d[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++)cin>>a[i],a[i+n]=a[i],sum+=a[i];
	stack<pair<int,int>> sta;
	sta.push({1,1});
	for(int i=2;i<=n*2;i++){//第一次1~n处理出以每个点为终点的连续大于他的数量，第二次求解差分数组
		int pos=1;
		while(!sta.empty()&&a[sta.top().first]>a[i]){
			if(i>n)d[pos]-=a[sta.top().first]-a[i];
			pos+=sta.top().second;
			if(i>n)d[pos]+=a[sta.top().first]-a[i];
			sta.pop();
		}
		sta.push({i,pos});
	}
	for(int i=1;i<=n;i++)d[i]+=d[i-1];
	for(int i=1;i<=n;i++){sum+=d[i];cout<<sum<<" ";}
}