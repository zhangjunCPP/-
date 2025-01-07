#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int ans[N];
int main(){
	int n,m;
	cin>>n>>m;
	int cnt=0;
	for(int i=1;i<=n;i++){
		ans[i]=i;
		cnt+=(i-1)/2;
		if(cnt>=m){
			ans[i]+=2*(cnt-m);
			int tmp=1e9;
			for(int j=n;j>i;j--)ans[j]=tmp,tmp-=ans[i]+1;
			for(int j=1;j<=n;j++)cout<<ans[j]<<" ";
			return 0;
		}
	}
	puts("-1");
}