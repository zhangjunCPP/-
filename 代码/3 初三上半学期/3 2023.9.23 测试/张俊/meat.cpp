#include<bits/stdc++.h>
#include<vector>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1e5+10;
struct node{
	int v,nex,id;
}a[N*4];
int first[N],cnt;
void add(int u,int v,int id){
	a[++cnt]={v,first[u],id};
	first[u]=cnt;
}
int val[N];
int ans=0;
map<vector<int> ,bool > mp;

void dfs(int u,vector<int> x){
	if(x.size()==9){
		if(x[0]==x[7]){
			if(x[0]!=x[1]&&x[0]!=x[3]&&x[0]!=x[5]&&x[1]!=x[3]&&x[1]!=x[5]&&x[3]!=x[5]){
				vector<int> tmp1,tmp2,tmp3;
				tmp1.push_back(x[0]);tmp1.push_back(x[1]);tmp1.push_back(x[3]);tmp1.push_back(x[5]);
				sort(tmp1.begin(),tmp1.end());
			
				tmp2.push_back(x[2]);tmp2.push_back(x[4]);tmp2.push_back(x[6]);tmp2.push_back(x[8]);
				sort(tmp2.begin(),tmp2.end());
			
				for(int i:tmp1) tmp3.push_back(i);
				for(int i:tmp2) tmp3.push_back(i);

				if(!mp[tmp3]){
					int sum=0;
					for(int i:tmp1){
						sum+=val[i];
					} 
					ans+=sum;
					mp[tmp3]=true;
				}
			}
		}
		return ;
	}
	int siz=x.size();
	int fa;
	if(siz==1) fa=0;
	if(siz==2) fa=x[0];
	else fa=x[siz-1-1-1];
	for(int i=first[u];i;i=a[i].nex){
		if(a[i].v==fa) continue;
		x.push_back(a[i].v);
		x.push_back(a[i].id);
		dfs(a[i].v,x);
		x.pop_back();
		x.pop_back();
	}
	return ;
}
signed main() {
	freopen("meat.in","r",stdin);
	freopen("meat.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>val[i];
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y,i);
		add(y,x,i);
	}
	for(int i=1;i<=n;i++){
		vector<int> x;
		x.push_back(i);
		dfs(i,x);
	}
	cout<<ans;
}

