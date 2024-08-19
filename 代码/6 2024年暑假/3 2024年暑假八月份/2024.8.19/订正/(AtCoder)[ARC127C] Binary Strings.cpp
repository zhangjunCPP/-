#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
bitset<N>s;
int main(){
	int n;
	cin>>n>>s;
	int sum=s.count();
	putchar('1');
	for(int i=n-1;i>=0;i--) {
		if(sum==1&&s[0])break;
		if(s[i]&&sum>1)s[i]=0,sum--,putchar('1');
		else {
			int pos=s._Find_first();
			for(int j=0;j<pos;j++)s[j]=1,sum++;
			s[pos]=0,sum--;
			putchar('0');
		}
	}
}