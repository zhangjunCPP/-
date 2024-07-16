#include <bits/stdc++.h>
using namespace std;
int main() {
	string s;
	cin>>s;
	int n=s.size();
	int m;
	cin>>m;
	while(m--) {
		string opt;
		cin>>opt;
		if(opt=="Q") {
			int x,y;
			cin>>x>>y;
			x--,y--;
			int ans=0;
			for(int i=x,j=y;i<n&&j<n;i++,j++) {
				if(s[i]==s[j])ans++;
				else break;
			}
			cout<<ans<<"\n";
		}
		else if(opt=="R") {
			int x;char d;
			cin>>x>>d;
			s[x-1]=d;
		}
		else {
			int x;string d;
			cin>>x>>d;
			s.insert(x,d);
			n++;
		}
	}
}