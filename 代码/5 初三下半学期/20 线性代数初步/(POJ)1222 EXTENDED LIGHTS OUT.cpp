#include <iostream>
#include <cstring>
using namespace std;
const int N=30;
int a[N+5][N+5];
int ans[N+5];
void solve(){
	memset(a,0,sizeof a);
	for(int i=1;i<=N;i++)cin>>a[i][N+1];
	for(int i=1;i<=5;i++){
		for(int j=1;j<=6;j++){
			int tmp=(i-1)*6+j;
			a[tmp][tmp]=1;
			if(i!=1)a[tmp][tmp-6]=1;
			if(i!=5)a[tmp][tmp+6]=1;
			if(j!=1)a[tmp][tmp-1]=1;
			if(j!=6)a[tmp][tmp+1]=1;
		}
	}
	for(int i=1;i<=N;i++){
		for(int j=i;j<=N;j++)if(a[j][i]){swap(a[i],a[j]);break;}
		if(!a[i][i])break;
		for(int j=1;j<=N;j++){
			if(j==i)continue;
			if(a[j][i])for(int k=i+1;k<=N+1;k++)a[j][k]^=a[i][k];
			a[j][i]=0;
		}
	}
	for(int i=N;i;i--){
		int sum=0;
		for(int j=i+1;j<=N;j++)sum^=a[i][j]&ans[j];
		ans[i]=sum^a[i][N+1];
	}
	for(int i=1;i<=30;i++){
		cout<<ans[i]<<" ";
		if(i%6==0)cout<<"\n";
	}
}

int main(){
	int T;
	cin>>T;
	for(int i=1;i<=T;i++){cout<<"PUZZLE #"<<i<<"\n";solve();}
	return 0;
}