#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
vector<char> sta[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	string s;
	cin>>s;
	int n=s.size();
	int dep=0,sum=0;
	int i=0;
	while(i<n) {
		int j=i;
		while(j<n&&s[j]=='(')sta[dep].push_back('('),j++,sum++;
		dep++;
		for(int tmp=sum;j<n&&tmp;j++) {
			sta[dep].push_back(s[j]);
			if(s[j]==')')tmp--;
			sum+=s[j]=='('?1:-1;
		}
		i=j;
	}
	dep=0;
	while(!sta[dep].empty()) {
		char tmp=sta[dep].back();
		cout<<sta[dep].back();
		sta[dep].pop_back();
		dep+=tmp=='('?1:-1;
	}
	return 0;
}