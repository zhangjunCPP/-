#include <bits/stdc++.h>
using namespace std;
int a[100000000];
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	int p=-1,q=-1;
	for(int i=1;i<=n+1;i++){
		int tmp=a[i]-a[i-1];
		if(tmp>=0){
			p=min(q,p+tmp);
			q=q+tmp;
		}
		else{
			p=max(min(q+tmp,p),-1);
			if(q>=a[i]){
				ans++;
				q=p;
				p=-1;
			}
		}
	}
	cout<<ans;
}