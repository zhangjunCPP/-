#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
char s1[N],s2[N];
void solve(){
	cin>>s1>>s2;
	int siz1=strlen(s1),siz2=strlen(s2);
	reverse(s1,s1+siz1);reverse(s2,s2+siz2);
	for(int i=siz1;i<siz2;i++) s1[siz1++]='0';
	while (siz1&&s1[siz1-1]==s2[siz2-1])--siz1,--siz2;
	if (siz1==0)puts("0");
	else cout<<(siz1-1)*9+llabs(s1[siz1-1]-s2[siz1-1])<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}