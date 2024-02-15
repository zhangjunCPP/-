#include<bits/stdc++.h>
using namespace std;
void solve(){
	int a,b;
	cin>>a>>b;
	if(a>b)swap(a,b);
	if(a%2==0){
		int x=a/2,y=b*2;
		if(x>y)swap(x,y);
		if(x!=a||y!=b){puts("Yes");return;}
	}
	if(b%2==0){
		int x=b/2,y=a*2;
		if(x>y)swap(x,y);
		if(x!=a||y!=b){puts("Yes");return;}
	}
	puts("No");
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
