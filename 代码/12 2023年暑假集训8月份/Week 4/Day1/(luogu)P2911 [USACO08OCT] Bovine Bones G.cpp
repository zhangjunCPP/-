#include<bits/stdc++.h>
using namespace std;
int sum[100000];
int main(){
	int s1,s2,s3;
	cin>>s1>>s2>>s3; 
	for(int i=1;i<=s1;i++){
		for(int j=1;j<=s2;j++){
			for(int k=1;k<=s3;k++){
				sum[i+j+k]++;
			}
		}
	}	
	int MAX=-1;
	for(int i=1;i<=s1+s2+s3;i++) MAX=max(MAX,sum[i]);
	for(int i=1;i<=s1+s2+s3;i++) if(sum[i]==MAX){
		cout<<i<<"\n";
		return 0;
	}

	return 0;
}

