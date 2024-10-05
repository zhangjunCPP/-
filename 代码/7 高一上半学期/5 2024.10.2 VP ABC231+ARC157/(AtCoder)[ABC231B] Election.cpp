#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
map<string,int>mp;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		mp[s]++;
	}
	int Max=-1;
	string ans;
	for(auto it:mp){
		if(it.second>Max){Max=it.second;ans=it.first;}
	}
	cout<<ans;
}