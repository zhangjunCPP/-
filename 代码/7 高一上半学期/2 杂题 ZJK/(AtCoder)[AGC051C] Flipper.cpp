#include<bits/stdc++.h>
using namespace std;
int P[3],S[3];
map<int,int>p,s[3];
int tmp_P[3],tmp_S[3];
int solve(int x,int y,int z){
	for(int i=0;i<3;i++)tmp_P[i]=P[i],tmp_S[i]=S[i];
	if( ((tmp_P[x]^tmp_S[x])&1) || ((tmp_P[y]^tmp_S[y])&1) || ((tmp_P[z]^tmp_S[z])&1) )tmp_S[x]--,tmp_S[y]++,tmp_S[z]++;
	int tmp=max(min({tmp_S[x]-tmp_P[x],tmp_P[y]-tmp_S[y],tmp_P[z]-tmp_S[z]}),0);
	tmp_S[x]-=tmp,tmp_S[y]+=tmp,tmp_S[z]+=tmp;
	return max(tmp_S[x],tmp_P[x])+max(tmp_S[y],tmp_P[y])+max(tmp_S[z],tmp_P[z]);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		swap(x,y);
		P[x%3]-=p[x];
		p[x]^=1;
		P[x%3]+=p[x];

		S[x%3]-=s[x%3][y];
		s[x%3][y]^=1;
		S[x%3]+=s[x%3][y];

		if(s[0][y]+s[1][y]+s[2][y]>1){
			S[0]-=s[0][y];S[1]-=s[1][y];S[2]-=s[2][y];
			s[0][y]^=1;s[1][y]^=1;s[2][y]^=1;
			S[0]+=s[0][y];S[1]+=s[1][y];S[2]+=s[2][y];
		}
	}
	cout<<min({n,solve(0,1,2),solve(1,0,2),solve(2,0,1)});
	return 0;
}