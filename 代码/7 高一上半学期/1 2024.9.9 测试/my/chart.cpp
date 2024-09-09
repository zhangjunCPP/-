#include<bits/stdc++.h>
using namespace std;
const int N=105;
string s;
int n,siz;
int sum[N];
int result[N];

int main(){
	cin>>s;
	siz=s.size();
	for(int i=0;i<siz;i++)if(s[i]>='a'&&s[i]<='z')n++;
	for(int i=1;i<=n;i++){
		char ch;
		int x;
		cin>>ch>>x;
		sum[ch-'a'+1]=x;
	}
	stack<pair<int,bool>> sta;
	int tot=0;
	for(int i=0;i<siz;i++){
		if(s[i]!=']')sta.push({s[i],true});
		else{
			int fir,sec;
			if(sta.top().second)sec=sta.top().first-'a'+1;
			else sec=sta.top().first;
			sta.pop(),sta.pop();
			if(sta.top().second)fir=sta.top().first-'a'+1;
			else fir=sta.top().first;
			sta.pop(),sta.pop();
			++tot;
			if(sum[fir]){
				if(sum[sec]){cout<<"No";return 0;}
				result[tot]=1;
				sum[fir]--;
			}
			else{
				result[tot]=0;
				sum[sec]--;
			}
			sta.push({result[tot]?fir:sec,false});
		}
	}
	for(int i=1;i<=26;i++)if(sum[i]){cout<<"No";return 0;
	}
	cout<<"Yes";
}

