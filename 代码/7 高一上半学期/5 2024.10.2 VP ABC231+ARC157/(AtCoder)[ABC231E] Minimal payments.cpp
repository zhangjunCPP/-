#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=60+10;
int a[N];
map<int,int>mp[N];
int dfs(int k,int x){
	if(k==1)return mp[k][x]=x;
	if(mp[k].count(x))return mp[k][x];
	int val1=x/a[k]+dfs(k-1,x%a[k]);//使用这种货币时不找零
	int val2=x/a[k]+1+dfs(k-1,(x/a[k]+1)*a[k]-x);
	return mp[k][x]=min(val1,val2);
}
signed main(){
	int n,x;
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<dfs(n,x);
}
/*
题目中说A_{i+1}是A_i的倍数，也就是说，一张大的能够完全等价于若干张小的。
那么容易想到，我们一定是先用大的，然后再用小的。
并且如果要找零，我一定只会多付一张。因为如果我多付了两张，根据上面先大后小的策略，他又会还给我一张
由于n只有60，记忆化搜索即可
*/