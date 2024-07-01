/*
T2
当流浪者说了后，那些不知道任何咒语的人就会离开。
因此，如果有不知道任何咒语的人，那第一天就会少人。
那么第一天来聚会的人就知道至少一条咒语。
我们考虑一个人A，他只知道一条咒语X，同时他知道知道X的所有人。
如果有一个人B，不在A所知道的知道X的集合中，但B第一天也参加了聚会，说明B知道A不知道的咒语，所以A第二天会离开。
因此我们记A知道的有咒语的人集合为S，则若第一天有S之外的人参与聚会，则A必须离开。
考虑第三天。
若S中有人离开，说明A知道的有咒语的人中有人不知道其他咒语。
记离开的人为C。
若A知道的咒语C均知道，那么C离开后，A也知道自己不知道其他咒语，因此A会离开。
-------
不对，我们求的是有人没来的**最早**的一次，因此我们对每天的讨论应该基于所有人都到齐的情况。因此第三天的讨论是错误的。

*/
#include<bits/stdc++.h>
using namespace std;
const int N=3e3+10;

int sum[N];
int unknow[N][2];
map<int,int> mp[N];
void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)mp[i].clear(),sum[i]=0;
	for(int i=1;i<=m;i++){
		cin>>unknow[i][0]>>unknow[i][1];
		for(int j=1;j<=n;j++)if(j!=unknow[i][0]&&j!=unknow[i][1])sum[j]++;		
	}
	bool flag=true;
	int num=0;
	//Day 1
	for(int i=1;i<=n;i++)if(sum[i]==0){flag=false;num++;}
	if(!flag){
		cout<<"1 "<<num<<"\n";
		for(int i=1;i<=n;i++)if(sum[i]==0)cout<<i<<" ";
		cout<<"\n";
		return;
	}
	if(k<=1){cout<<"-1\n";return;}
	//Day 2
	for(int i=1;i<=n;i++){
		int unknow1=-1,unknow2=-1;
		for(int j=1;j<=m;j++){
			if(i==unknow[j][0]||i==unknow[j][1])continue;
			if(unknow1==-1){unknow1=unknow[j][0],unknow2=unknow[j][1];continue;}
			if(unknow1!=unknow[j][0]&&unknow1!=unknow[j][1])unknow1=0;
			if(unknow2!=unknow[j][0]&&unknow2!=unknow[j][1])unknow2=0;
		}
		if(unknow1>=1||unknow2>=1){flag=false;num++;}
	}
	if(!flag){
		cout<<"2 "<<num<<"\n";
		for(int i=1;i<=n;i++){
			int unknow1=-1,unknow2=-1;
			for(int j=1;j<=m;j++){
				if(i==unknow[j][0]||i==unknow[j][1])continue;
				if(unknow1==-1){unknow1=unknow[j][0],unknow2=unknow[j][1];continue;}
				if(unknow1!=unknow[j][0]&&unknow1!=unknow[j][1])unknow1=0;
				if(unknow2!=unknow[j][0]&&unknow2!=unknow[j][1])unknow2=0;
			}
			if(unknow1>=1||unknow2>=1)cout<<i<<" ";
		}
		cout<<"\n";
		return;
	}
	cout<<"-1\n";
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}