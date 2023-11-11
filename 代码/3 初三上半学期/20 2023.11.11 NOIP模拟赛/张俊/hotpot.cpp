#include "hotpot.h"
#include<bits/stdc++.h>
const int N=1e5+10;
using namespace std;
vector<int> ans1,ans2;
int sum1[N],sum2[N];
void solve(int n){
	int t1=n/2;
	int t2=n-t1;
	
	for(int i=1;i<=t1;i++) {
		for(int j=1;j<=t2;j++) {
			bool ans=ask(i,j);
			if(ans) sum1[i]++;
			else sum2[j]++;
		}
	}
	
	for(int i=1;i<=t1;i++)ans1.push_back(sum1[i]*2);
	for(int i=1;i<=t2;i++)ans2.push_back(sum2[i]*2+1);
	report(ans1,ans2);
}
