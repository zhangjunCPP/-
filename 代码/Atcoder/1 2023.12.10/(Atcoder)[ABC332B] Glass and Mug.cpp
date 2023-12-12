#include<bits/stdc++.h>
using namespace std;
int a,b,c;
int main(){
	int k,g,m;
	cin>>k>>g>>m;
	for(int i=1;i<=k;i++){
		if(a==g)a=0;
		else if(b==0)b=m;
		else{
			c=min(g-a,b);
			a+=c,b-=c;
		}
	}
	cout<<a<<" "<<b;
	return 0;
}
