#include<bits/stdc++.h>
using namespace std;

int main(){
	srand(time(NULL));
	int n=rand()%10+1;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++) {
		cout<<rand()<<" ";
	}

	return 0;
}

