#include <bits/stdc++.h>

using namespace std;
const int N=5e5+10;
int n;
int p[N],c[N];
int a[N];
bool vis[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i];
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)a[i]=i;
	int ans=0x3f3f3f3f;
	do{
		int sum=0;
		for(int i=1;i<=n;i++)vis[i]=false;
		for(int i=1;i<=n;i++){
			if(vis[a[i]])continue;
			vis[a[i]]=true;//del i->p[i]
			sum+=c[a[i]];
			for(int j=1;j<=n;j++){
				if(j<a[i]&&p[j]>p[a[i]])vis[j]=true;
				if(j>a[i]&&p[j]<p[a[i]])vis[j]=true;
			}
		}
		ans=min(ans,sum);
	}while(next_permutation(a+1,a+n+1));
	cout<<ans;
}