#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
int a[N];
int ans[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],ans[i]=i;
	sort(ans+1,ans+n+1,[](const int&x,const int&y){
		if(a[x]!=a[y])return a[x]<a[y];
		return x>y;
	});
	for(int i=1;i<=n;i++)a[ans[i]]=i;
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
}