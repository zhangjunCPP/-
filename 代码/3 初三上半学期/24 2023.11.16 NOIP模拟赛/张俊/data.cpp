#include<bits/stdc++.h>
using namespace std;
int random(int l,int r){
	return rand()%(r-l+1)+l;
}
int main(){
	freopen("cut.in","w",stdout);
    srand(time(NULL));
	int n=random(1,25);
	int k=random(1,n);
	cout<<n<<" "<<k<<"\n";
	for(int i=2;i<=n;i++) {
		cout<<i<<" "<<random(1,i-1)<<"\n";
	}
	return 0;
}

