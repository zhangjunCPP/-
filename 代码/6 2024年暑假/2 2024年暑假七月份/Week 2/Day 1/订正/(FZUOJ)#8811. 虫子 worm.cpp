#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int n,q;
int block;
int b[N],w[N];
int nex[N][18][2];//0:black 1:white
void init_1(){
	for(int i=0;i<18;i++){
		nex[n][i][0]=b[n];
		nex[n][i][1]=w[n];
	}
	for(int i=0;i<18;i++){
		nex[n+1][i][0]=n+1;
		nex[n+2][i][0]=n+2;
		nex[n+1][i][1]=n+1;
		nex[n+2][i][1]=n+2;
	}
	for(int i=n-1;i;i--){
		nex[i][0][0]=b[i];
		nex[i][0][1]=w[i];
		for(int j=1;j<18;j++){
			nex[i][j][0]=nex[nex[i][j-1][0]][j-1][0];
			nex[i][j][1]=nex[nex[i][j-1][1]][j-1][1];
		}
	}
}
int ed[N][2];
int last[N][500][2];
void init_2(){
	for(int k=1;k<=block;k++){
		if(k==1)for(int i=1;i<=n;i++)ed[i][0]=b[i],ed[i][1]=w[i];
		else for(int i=1;i<=n;i++)ed[i][0]=b[ed[i][0]],ed[i][1]=w[ed[i][1]];
		last[n+1][k][0]=last[n+1][k][1]=n+1;
		last[n+2][k][0]=last[n+2][k][1]=n+2;
		for(int i=n;i>=1;i--){
			last[i][k][0]=last[ed[i][0]][k][1];
			last[i][k][1]=last[ed[i][1]][k][0];
		}
	}
}
int jump(int p,int k,int col){
	while(p!=n+1&&p!=n+2){
		for(int i=17;i>=0;i--)if((k>>i)&1)p=nex[p][i][col];
		col^=1;
	}
	return p-n-1;
}
signed main(){
	cin>>n>>q;
	block=sqrt(n);
	for(int i=1;i<=n;i++)cin>>b[i]>>w[i];
	b[n+1]=w[n+1]=n+1,b[n+2]=w[n+2]=n+2;
	init_1();
	init_2();
	while(q--){
		int p,k,col;
		cin>>p>>k>>col;
		if(k>=block)cout<<jump(p,k,col)<<"\n";
		else cout<<last[p][k][col]-n-1<<"\n";
	}
}