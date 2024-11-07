#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
vector<int>v[30];
int main(){
	int n;
	string s;
	cin>>n>>s;
	for(int i=1;i<=n;i++)v[s[i-1]-'a'].push_back(i);
	int ans=0;
	for(int i=0;i<26;i++){
		if(!v[i].empty())
			for(int j=0;j<26;j++){
				if(!v[j].empty()&&i!=j){
					int pos1=0,pos2=0;
					bool flag=false;
					int Min=-1;
					while(pos1<v[i].size()||pos2<v[j].size()){
						int val1=(pos1==v[i].size())?INF:v[i][pos1];
						int val2=(pos2==v[j].size())?INF:v[j][pos2];
						if(val1<val2) Min++,pos1++;
						if(val1>val2){
							if(flag) Min--;
							pos2++;
							flag=true;
						}
						if(Min<0) Min=-1,flag=false;
						ans=max(ans,Min);
					}
				}
			}
	}
	cout<<ans;
	return 0;
}