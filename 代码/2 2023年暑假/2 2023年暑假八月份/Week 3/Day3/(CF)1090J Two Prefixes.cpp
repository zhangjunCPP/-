#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int nex[N],cnt[N];
char s[N],t[N];

signed main(){
	cin>>(s+1)>>(t+1);
	int len1= strlen(s+1);
	int len2= strlen(t+1);
	for(int i=2,j=0;i<=len2;i++) {
		while(j&&t[j+1]!=t[i]) j=nex[j];
		if(t[j+1]==t[i]) nex[i]=j+1,j++;
	}
	for(int i=1,j=0;i<=len1;i++){
		while(j&&t[j+1]!=s[i]) j=nex[j];
		if(t[j+1]==s[i]) j++;
		if(j<i) cnt[j]++;
		else cnt[nex[j]]++;
	}
	for(int i=len2;i;i--) cnt[nex[i]]+=cnt[i];
	int ans=len1*len2;
	for(int i=1;i<=len2;i++){
		if (nex[i]&&i-nex[i]>0)ans-=cnt[i-nex[i]];
	}
	cout<<ans<<"\n";
}