#include<bits/stdc++.h>
using namespace std;
int main() {
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
	int T;
	cin>>T;
	while(T--) {
		int k;
		string s;
		cin>>k>>s;
		int tmp=pow(2,2*k+1);
		for(int i=1;i<=tmp;i++)cout<<0;
		cout<<"\n";
	}
}