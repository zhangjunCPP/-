#include<bits/stdc++.h>
using namespace std;
void calc_t1(int n,int x,int y,int k){
	if(abs(x-y)>=k)cout<<"1\n";
	else if(n-x>=k&&n-y>=k)cout<<"2\n";
	else if(x-1>=k&&y-1>=k)cout<<"2\n";
	else if(n-x>=k&&n-1>=k&&y-1>=k)cout<<"3\n";
	else if(n-y>=k&&n-1>=k&&x-1>=k)cout<<"3\n";
	else cout<<"-1\n";
}
void solve(){
	int t,n,k,x,y;
	cin>>t>>n>>k>>x>>y;
	if(x>y)swap(x,y);
	if(t==0){
		cout<<abs(x-y)<<"\n";
		return;
	}
	if(k==1){
		cout<<"1\n";
		return;
	}
	if(k==2){
		if(n==2)cout<<"-1\n";
		else if(n==3){
			if(t>1)cout<<"-1\n";
			else if((x==1&&y==3)||(x==3&&y==1))cout<<"1\n";
			else cout<<"-1\n";
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
			if(t>3)cout<<"-1\n";
			else{
				if(n==6&&x==2&&y==5)cout<<"1\n";
				else cout<<"-1\n";
			}
		}
		//t==2&&k==3
		else if(n==2||n==3||n==4)cout<<"-1\n";
		else{
			if(n==5){
				if(x==2&&y==4)cout<<"1\n";
				else cout<<"-1\n";
			}
			else if(n==6){
				if(x==2&&y==4)cout<<"1\n";
				else if(x==2&&y==3)cout<<"2\n";
				else if(x==2&&y==5)cout<<"3\n";
				else if(x==4&&y==3)cout<<"1\n";
				else if(x==4&&y==5)cout<<"2\n";
				else if(x==3&&y==5)cout<<"1\n";
				else cout<<"-1\n";
			}
			else if(n==7){
				if(x==3&&y==5)cout<<"1\n";
				else cout<<"-1\n";
			}
			else cout<<"-1\n";
		}
		return;
	}
	cout<<"-1\n";
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)solve();
}
/*
1
2 237540200 3 230025504 14975494
*/