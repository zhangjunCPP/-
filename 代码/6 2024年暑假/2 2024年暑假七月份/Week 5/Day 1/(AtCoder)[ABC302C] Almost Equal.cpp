#include<bits/stdc++.h>
using namespace std;
string s[105];
int n,m;
int a[105];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)a[i]=i;
	do {
		bool flag=true;
		for(int i=1;i<n;i++) {
			int sum=0;
			for(int j=0;j<m;j++)sum+=s[a[i]][j]!=s[a[i+1]][j];
			if(sum!=1) {
				flag=false;
				break;
			}
		}
		if(flag){puts("Yes");return 0;}
	}while(next_permutation(a+1,a+n+1));
	puts("No");
}