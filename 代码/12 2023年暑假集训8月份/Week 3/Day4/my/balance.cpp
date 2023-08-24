#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int v,nex;

}a[N];
int first[N],cnt;
void add(int u,int v){
	a[++cnt]={v,first[u]};
	first[u]=cnt;
}
int main(){

	freopen("balance.in","r",stdin);
	freopen("balance.out","w",stdout);
	int n;
	cin>>n; 
	bool flag1=true,flag2=true;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		if(u!=i||v!=i+1) flag1=false;
		if(u!=1||v!=i+1) flag2=false;
	}
	if(flag1){
		
	}
	if(flag2){
		for(int i=1;i<=n;i++){
			if(i==1) cout<<2<<"\n";
			else cout<<1<<"\n";
		}
		return 0;
	}
	return 0;
}

