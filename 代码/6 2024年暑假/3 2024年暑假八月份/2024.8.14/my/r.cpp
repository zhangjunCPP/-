#include<bits/stdc++.h>
using namespace std;
map<int,int> vis;
void solve() {
	int n;
	cin>>n;
	if(n==2) {cout<<"3 1\n";return;}
	if(n==3) {cout<<"7 6 3\n";return;}
	if(n==4) {cout<<"25 21 23 31\n";return;}
	if(n==5) {cout<<"20 29 18 26 28\n";return;}
	for(int Min=1;Min<=1000;Min++) {
		for(int Sqrt=2;Sqrt<=1100;Sqrt++) {
			vector<int>ans;
			vis.clear();
			int sum=Sqrt*Sqrt;
			int Max=Sqrt+Min;
			if(Max-Min<n-1)continue;
			sum-=Min+Max;
			int tmp=(n-1)*(n-2)/2+Min*(n-2);
			if(sum<tmp)continue;
			tmp=Max*(n-2)-(n-1)*(n-2)/2;
			if(sum>tmp)continue;
			sum-=Min*(n-2);
			if((n-2)&1) {
				int team=(n-2)/2;
				int last=sum-(sum/team*team);
				sum-=last;
				if(last==0)continue;
				ans.emplace_back(Max);ans.emplace_back(Min);ans.emplace_back(Min+last);
				vis[Max]++,vis[Min]++,vis[Min+last]++;
				int team_sum=sum/team;
				int x=Min+last+1,y=Min+(team_sum-(last+1));
				while(y>=Max)x++,y--;
				for(int i=1;i<=team;i++) {
					ans.emplace_back(x);ans.emplace_back(y);
					vis[x]++,vis[y]++;
					x++,y--;
				}
			}
			else {
				int team=(n-2)/2;
				int team_sum=sum/team;
				ans.emplace_back(Max);ans.emplace_back(Min);
				vis[Max]++;vis[Min]++;
				int x=Min+1,y=Min+(team_sum-1);
				while(y>=Max)x++,y--;
				for(int i=1;i<=team;i++) {
					ans.emplace_back(x);ans.emplace_back(y);
					vis[x]++,vis[y]++;
					x++,y--;
				}
			}
			bool flag=true;
			for(int i:ans)if(vis[i]>1){flag=false;break;}
			if(flag){for(int i:ans)cout<<i<<" ";cout<<"\n";return;}
		}
	}
}
int main() {
	freopen("r.in","r",stdin);
	freopen("r.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
}