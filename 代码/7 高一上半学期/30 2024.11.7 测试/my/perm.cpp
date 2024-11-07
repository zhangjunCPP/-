#include<bits/stdc++.h>
#define int long long
using namespace std;
int f(int n,int now,int opt){
	int tmp=(n-(now+opt))/2+1;
	int tmp4=tmp%now,tmp5=(tmp+now-1)/now;
	int last=tmp5*now/2;
	int x;
	if(tmp4<=now/2-1&&tmp4>=1)x=last-((now/2-tmp4));
	else x=last;
	return (x&1);
}
void calc(int n){
	if(n==1||n==2)cout<<2<<"\n";
	else if(n==3)cout<<0<<"\n";
	else{
		int ans=2;
		if(n&1)ans^=(3+1)^(1+2)^(2+3);
		if(n&1){
			int ans2=0;
			int tmp2=(n-7)/2+1;
			int tmp3=(tmp2+1)/2;
			ans2=(((n-3)/2)&1)*2+(tmp3&1)*4;
			int now=4;
			for(int i=3;i<=63;i++){
				//以now为周期，从now+1开始
				if(n<now+1)break;
				ans2=ans2+f(n,now,1)*now*2;
				now*=2;
			}
			cout<<(ans2^ans);
		}
		else{
			int ans2=0;
			int tmp2=(n-6)/2+1;
			int tmp3=(tmp2+1)/2;
			ans2=(tmp3&1)*4;
			int now=4;
			for(int i=3;i<=63;i++){
				//以now为周期，从now开始
				if(n<now)break;
				ans2=ans2+f(n,now,0)*now*2;
				now*=2;
			}
			cout<<(ans2^ans);
		}
	}
}
signed main(){
	int n;
	cin>>n;
	calc(n);
}
/*
当n=1时，a=1
当n=2时，a={2,1}
否则，a={3,1,2,4……}
先排除n=1和2的情况
若n为偶数，则4+4,6+6,8+8,……,n+n会产生贡献
否则，3+1,1+2,2+3（特殊）,5+5,7+7,9+9,……,n+n会产生贡献
*/