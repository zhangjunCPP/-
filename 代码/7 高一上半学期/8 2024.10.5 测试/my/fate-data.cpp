#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int col[N];
int main(){
	freopen("fate10.in","w",stdout);
	int n=1e6-1;
	cout<<n<<"\n";
	int tot=0;
	for(int i=1;i<=n;i++)col[i]=col[i+n]=++tot;
	for(int i=1;i<=n*2;i++)cout<<col[i]<<" ";
}