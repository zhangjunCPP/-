#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int n,k;
int sum[N];
struct node{
	string s;
	int id;
};
int h[N];
int rk[N],sa[N];
bool cmp(const node &s,const node &t){return s.s>t.s;}
void dfs(int x,string s){
	if(x>n){
		vector<node> tmp;
		for(int i=1;i<=n;i++){
			string u="";
			for(int j=i;j<=n;j++)u+=s[j];
			tmp.push_back((node){u,i});
		}
		sort(tmp.begin(),tmp.end(),cmp);
		int siz=tmp.size();
		for(int i=0;i<siz;i++)sa[i+1]=tmp[i].id;
		for(int i=1;i<=n;i++) rk[sa[i]]=i;
		
		int kk=0;
		for(int i=1;i<=n;i++){
			if(rk[i]==0) continue;
			if(kk) kk--;
			int tmp1=sa[rk[i]];
			int tmp2=sa[rk[i]-1];
			while(tmp1+kk<=n&&tmp2+kk<=n&&s[tmp1+kk]==s[tmp2+kk]) kk++;
			h[rk[i]]=kk;
		}
		int ans=n*(n+1)/2;
		for(int i=1;i<=n;i++) ans-=h[i]/2;
		cout<<s<<" "<<ans<<"\n";
		sum[ans]++;
		cout<<"\n\n";
		return;	
	}
	dfs(x+1,s+'0');
	dfs(x+1,s+'1');
}
int main(){
	cin>>n>>k;
	string tmp="T";
	dfs(1,tmp);
	for(int i=1;i<=k;i++){
		cout<<sum[i]<<" ";
	}
	return 0;
}

