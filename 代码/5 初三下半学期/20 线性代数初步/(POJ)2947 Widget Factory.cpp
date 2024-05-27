#include <string>
#include <map>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;
int n,m;
map<string,int> mp;
const int N=1e3+10;
int a[N][N];
int f(int x){return (x%7+7)%7;}
int inv(int x){return pow(x,5);}
int Guass(){
	int flag=1;
	for(int i=1;i<=n;i++){
		for(int j=flag;j<=m;j++)if(a[j][i]%7){swap(a[flag],a[j]);break;}
		if(!a[flag][i])continue;
		int p=inv(a[flag][i]);
		for(int j=1;j<=n+1;j++)a[flag][j]=a[flag][j]*p%7;
		for(int j=1;j<=m;j++){
			if(j==flag)continue;
			if(a[j][i]){
				int tmp=a[j][i];
				for(int k=1;k<=n+1;k++)a[j][k]=f(a[j][k]-a[flag][k]*tmp);
			}
		}
		flag++;
	}
	for(int i=1;i<=m;i++){
		if(!a[i][n+1])continue;
		int sum=0;
		for(int j=1;j<=n;j++)sum+=a[i][j];
		if(!sum)return 0;
	}
	if(flag<=n)return -1;
	else return 1;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	mp["MON"]=1,mp["TUE"]=2,mp["WED"]=3,mp["THU"]=4,mp["FRI"]=5,mp["SAT"]=6,mp["SUN"]=7;
	cin>>n>>m;
	while(n!=0||m!=0){
		memset(a,0,sizeof a);
		for(int i=1;i<=m;i++){
			int sum;
			string s1,s2;
			cin>>sum>>s1>>s2;
			a[i][n+1]=f(mp[s2]-mp[s1]+1-sum*3);
			for(int j=1;j<=sum;j++){
				int x;
				cin>>x;
				a[i][x]++;a[i][x]%=7;
			}
		}
		int ans=Guass();
		if(ans==1){
			for(int i=1;i<n;i++)cout<<a[i][n+1]+3<<" ";
			cout<<a[n][n+1]+3<<"\n";
		}
		else if(ans==0)cout<<"Inconsistent data.\n";
		else cout<<"Multiple solutions.\n";
		cin>>n>>m;
	}
}