#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int> q;
int ans;
int n;
int val[N];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>val[i];
	cin>>ans;
	for(int i=1;i<=n;i++) {
		int x;
		cin>>x;
		q.push_back(x);
	}
	
	stack<int> s;
	int num=0;
	for(int i:q){
		while(s.size()&&s.top()>i){
			num+=val[i];
			s.pop();
		} 
		s.push(i);
	}

	if(num!=ans) puts("WA");
	else puts("AC");
	return 0;
}

