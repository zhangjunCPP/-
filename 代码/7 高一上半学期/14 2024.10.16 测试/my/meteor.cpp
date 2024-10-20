#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int INF=1e9;
struct node{
	int l,r,d;
};
node G[N];
bool vis[N];
int tot;
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	G[0]={1,n,0};
	for(int T=1;T<=m;T++){
		int opt,l,r,d;
		cin>>opt>>l>>r>>d;
		if(opt==1){
			G[T]={l,r,d};
		}
		else{
			for(int i=T;i;i--){
				if(!d)continue;
				if(vis[i])continue;
				if(!G[i].d)continue;
				if(l>G[i].r||r<G[i].l)continue;
				if(d<G[i].d){G[i].d-=d;d=0;cout<<i<<" ";if(!G[i].d)vis[i]=true;}
				else{
					d-=G[i].d;
					G[i].d=0;vis[i]=true;
					cout<<i<<" ";
				}
			}
			if(d)cout<<0;
			cout<<"\n";
		}
	}
}