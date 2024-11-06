#include<bits/stdc++.h>
using namespace std;
const int N=6000+10;
int sum[N][N];
int calc(int x_1,int y_1,int x_2,int y_2){
	return sum[x_2][y_2]-sum[x_1-1][y_2]-sum[x_2][y_1-1]+sum[x_1-1][y_1-1];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m,s;
	cin>>n>>m>>s;
	int tot=0;
	for(int i=1;i<=n;i++){
		string str;
		cin>>str;
		for(int j=1;j<=m;j++)sum[i][j]=str[j-1]-'0',tot+=str[j-1]-'0';
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)sum[i][j]+=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
	}
	int ans1=0;
	long long ans2=0;
	for(int i=1;i<=n;i++){
		int len=0;
		for(int j=m;j;j--){
			while(len<min(n-i+1,m-j+1)&&calc(i,j,i+len,j+len)<=s)len++;
			while(len&&calc(i,j,i+len-1,j+len-1)>s)len--;
			ans1=max(ans1,len);
			ans2+=len;
		}
	}
	cout<<ans1<<" "<<ans2;
}