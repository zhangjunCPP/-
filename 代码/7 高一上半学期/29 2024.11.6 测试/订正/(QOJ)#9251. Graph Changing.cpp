#include<bits/stdc++.h>
using namespace std;
void calc_t1(int n,int x,int y,int k){
	if(abs(x-y)>=k)puts("1");
	else if(n-x>=k&&n-y>=k)puts("2");
	else if(x-1>=k&&y-1>=k)puts("2");
	else if(n-x>=k&&n-1>=k&&y-1>=k)puts("3");
	else if(n-y>=k&&n-1>=k&&x-1>=k)puts("3");
	else puts("-1");
}
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}
void solve(){
	int t,n,k,x,y;
	t=read(),n=read(),k=read(),x=read(),y=read();
	if(x>y)swap(x,y);
	if(t==0){
		cout<<abs(x-y)<<"\n";
		return;
	}
	if(k==1){
		puts("1");
		return;
	}
	if(k==2){
		if(n==2)puts("-1");
		else if(n==3){
			if(t>1)puts("-1");
			else if((x==1&&y==3)||(x==3&&y==1))puts("1");
			else puts("-1");
		}
		else if(t&1){
			calc_t1(n,x,y,k);
		}
		else cout<<abs(x-y)<<"\n";
		return;
	}
	if(t==1){
		calc_t1(n,x,y,k);
		return;
	}
	if(k==3){
		if(t>2){
			if(t>3)puts("-1");
			else{
				if(n==6&&x==2&&y==5)puts("1");
				else puts("-1");
			}
		}
		//t==2&&k==3
		else if(n==2||n==3||n==4)puts("-1");
		else{
			if(n==5){
				if(x==2&&y==4)puts("1");
				else puts("-1");
			}
			else if(n==6){
				if(x==2&&y==4)puts("1");
				else if(x==2&&y==3)puts("2");
				else if(x==2&&y==5)puts("3");
				else if(x==3&&y==4)puts("1");
				else if(x==4&&y==5)puts("2");
				else if(x==3&&y==5)puts("1");
				else puts("-1");
			}
			else if(n==7){
				if(x==3&&y==5)puts("1");
				else puts("-1");
			}
			else puts("-1");
		}
		return;
	}
	puts("-1");
}
int main(){
	int T=read();
	while(T--)solve();
}