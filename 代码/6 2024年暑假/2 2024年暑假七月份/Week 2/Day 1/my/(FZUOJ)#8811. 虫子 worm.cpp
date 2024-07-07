#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int b[N],w[N];
int nex[N][18][2];//0:black 1:white
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>b[i]>>w[i];
	//i=n
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
	while(q--){
		int p,k,col;
		cin>>p>>k>>col;
		int LOG=log2(k)+1;
		while(p!=n+1&&p!=n+2){
			for(int i=LOG;i>=0;i--)if((k>>i)&1)p=nex[p][i][col];
			col^=1;
		}
		cout<<p-n-1<<"\n";
	}
}
/*
 *  考虑倍增
 *  设nex[x][i][col]表示从x跳相同颜色的格子2^i个所到达的位置
 *  然后直接暴力跳？
 *  最坏可到 n^2，可以卡到50分，但我相信出题人是好人，给我不止50分
 */