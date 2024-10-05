#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;

int main(){
	int n,a,b,c,d;
	cin>>n>>a>>b>>c>>d;
	cout<<(abs(b-c)<=1?(!b&&!c&&a&&d?"No":"Yes"):"No");
	return 0;
}