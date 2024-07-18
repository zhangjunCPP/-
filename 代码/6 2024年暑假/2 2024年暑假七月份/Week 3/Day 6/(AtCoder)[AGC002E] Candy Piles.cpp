#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N];
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++) {
		if(i+1>a[i+1]) {
			int dis=0;
			while(a[i+dis+1]==i)dis++;
			if(((a[i]-i)&1)||(dis&1))puts("First");
			else puts("Second");
			break;
		}
	}
}