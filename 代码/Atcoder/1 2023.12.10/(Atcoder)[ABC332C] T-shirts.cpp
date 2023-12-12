#include<bits/stdc++.h>
using namespace std;
int ans;
int sum1,sum2;
int main(){
	int n,m;
	string s;
	cin>>n>>m>>s;
	s+="0";
	for(int i=0;i<=n;i++){
		if(s[i]=='0'){
			ans=max({ans,sum1+sum2-m,sum2});
			sum1=0,sum2=0;
		}
		if(s[i]=='1')sum1++;
		if(s[i]=='2')sum2++;
	}
	cout<<ans;
	return 0;
}
