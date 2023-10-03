#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N],b[N];
int q[N],tot;
int lastpos[N],endpos[N];
bool vis[N],vis2[N]; 
int ans[N];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		if(tot==i-1){
			if(!vis[a[i]]){
				vis[a[i]]=true;
				q[++tot]=a[i];
			}
			else if(!vis[b[i]]){
				vis[b[i]]=true;
				q[++tot]=b[i];
				vis2[i]=true;
			}
		}
	}
	if(tot==n){
		for(int i=1;i<=n;i++){
			if(vis[b[i]]||vis2[i]) break;
			vis[b[i]]=true;
			q[++tot]=b[i];
		}
	}
	for(int i=tot;i;i--){
		lastpos[q[i]]=i;
		if(i>n||vis[b[i]]||vis2[i]){
			endpos[i]=i>n?i-n:i;
			ans[endpos[i]]++;
		}
		else {
			endpos[i]=endpos[lastpos[b[i]]];
			ans[endpos[i]]++;
		}
		vis[q[i]]=false;
	}
	ans[tot%n+1]+=ans[0]+m-tot;
	for(int i=1;i<=n;i++) cout<<ans[i]<<"\n";
	return 0;
}
