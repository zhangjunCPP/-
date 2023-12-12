#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m;
int Max1[N],Max2[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=0;j<m;j++){	
			if(j==0)Max1[i]=Max2[i]=s[j]-'a';
			else {
				Max1[i]=min(Max1[i],s[j]-'a');
				Max2[i]=max(Max2[i],s[j]-'a');
			}
		}
	}
	for(int i=1;i<=n;i++){		
		bool flag=true;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			if(Max1[i]<Max2[j])continue;
			else{
				flag=false;
				putchar('0');
				break;			
			}
		} 
		if(flag==1)putchar('1');
	}
	return 0;
}
