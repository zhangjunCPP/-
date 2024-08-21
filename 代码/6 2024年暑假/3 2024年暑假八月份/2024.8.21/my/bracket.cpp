#include<bits/stdc++.h>
using namespace std;
const int N=3e6+10;
int suml[N],sumr[N];
int main() {
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	freopen("bracket.in","r",stdin);
	freopen("bracket.out","w",stdout);
	string s;
	cin>>s;
	int n=s.size();
	int top=0;
	for(int i=0;i<n;i++) {
		if(s[i]=='(')top++;
		else if(top)top--;
		else {cout<<"-1";return 0;}
		suml[i]=top;
	}
	if(top){cout<<"-1";return 0;}
	top=0;
	for(int i=n-1;i>=0;i--) {
		if(s[i]==')')top++;
		else if(top)top--;
		else {cout<<"-1";return 0;}
		sumr[i]=top;
	}
	int ans=0;
	for(int i=0;i<n;i++)ans=max(ans,min(suml[i],sumr[i+1]));
	cout<<n-ans*2;
}
/*
 *考虑求出到一个位置时左/右两边未匹配左/右的数量
 *那么就可以枚举一个位置，左边选左括号，右边选右括号，能组成的最大值即为两者的最小值*2
 */