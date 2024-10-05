#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10,M=1e6+10;
int a[N][N];
int Min_x[M],Min_y[M],Max_x[M],Max_y[M];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++)Min_x[i]=Min_y[i]=1e9;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			Min_x[a[i][j]]=min(Min_x[a[i][j]],i);
			Max_x[a[i][j]]=max(Max_x[a[i][j]],i);
			Min_y[a[i][j]]=min(Min_y[a[i][j]],j);
			Max_y[a[i][j]]=max(Max_y[a[i][j]],j);
		}
	}
	for(int i=1;i<=k;i++){
		int len=max(Max_x[i]-Min_x[i]+1,Max_y[i]-Min_y[i]+1);
		if(Min_x[i]==1e9)len=0;
		cout<<len*len<<"\n";
	}
}