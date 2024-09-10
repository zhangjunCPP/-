#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
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