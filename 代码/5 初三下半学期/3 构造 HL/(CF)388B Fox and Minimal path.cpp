#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010;
bool ans[N][N];
int calc(int k,int i){
	int tmp=k/pow(10,i);
	return tmp%10;
}
signed main(){
	int k;
	cin>>k;
	int n=2;
	int Max=-1;
	if(k==1){
		cout<<2<<"\n";
		cout<<"NY\nYN";
		return 0;
	}
	for(int i=9;i>=0;i--){
		int tmp=calc(k,i);
		if(tmp<10&&tmp>0){
			if(i!=0){
				for(int l=1;l<=tmp;l++)ans[1][n+l]=1;
				for(int l=1;l<=tmp;l++)ans[n+l][n+tmp+1]=1;
				n+=tmp+1;
				for(int l=1;l<=10;l++)ans[n][n+l]=1;
				for(int j=1;j<=i-1;j++){
					for(int l=1;l<=10;l++)for(int m=1;m<=10;m++)ans[n+l][n+10+m]=1;
					n+=10;
				}
				if(Max==-1){
					for(int l=1;l<=10;l++)ans[n+l][2]=1;
					n+=10;
					Max=i+2;
				}else{
					for(int l=1;l<=10;l++)ans[n+l][n+10+1]=1;
					n+=10;
					for(int j=1;j<=Max-2-i-1;j++){
						ans[n+1][n+2]=1;
						n++;
					}
					ans[n+1][2]=1;
					n++;
				}
			}
			else {
				// cout<<n<<" "<<Max<<"\n";
				int now=k%10;
				if(Max==-1||Max==1){
					for(int l=1;l<=now;l++)ans[1][n+l]=1;
					for(int l=1;l<=now;l++)ans[n+l][2]=1;
					n+=now;
				}
				else{
					for(int l=1;l<=now;l++)ans[1][n+l]=1;
					for(int l=1;l<=now;l++)ans[n+l][n+now+1]=1;
					n+=now;
					for(int j=1;j<=Max-i-1-1;j++){ans[n+1][n+2]=1;n++;}
					ans[n+1][2]=1;
					n++;
				}
				break;
			}

		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(ans[i][j]||ans[j][i])ans[i][j]=ans[j][i]=1;
		}
	}
	for(int i=1;i<=n;i++)ans[i][i]=0;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(ans[i][j])cout<<"Y";
			else cout<<"N";
		}
		cout<<"\n";
	}
}