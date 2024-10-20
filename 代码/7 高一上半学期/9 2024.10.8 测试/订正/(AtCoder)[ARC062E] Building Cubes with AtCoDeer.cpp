#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
struct node{
	int c[5];
	bool operator<(const node&oth)const{
		for(int i=0;i<4;i++)if(c[i]!=oth.c[i])return c[i]<oth.c[i];
		return false;
	}
	void init(){cin>>c[0]>>c[1]>>c[2]>>c[3];}
	node find_min(){
		node ans=*this;
		for(int i=0;i<4;i++){
			node tmp;
			for(int j=0;j<4;j++)tmp.c[j]=c[(i+j)%4];
			ans=min(ans,tmp);
		}
		return ans;
	}
}a[N];
map<node,int> mp;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i].init();
		a[i]=a[i].find_min();
		mp[a[i]]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){//选i和j作为顶面和底面
			mp[a[i]]--,mp[a[j]]--;
			for(int k=0;k<4;k++){//枚举顶面和底面旋转组成的4种情况(顶面顺时针为：0,1,2,3 底面顺时针为：k,k+3,k+2,k+1 (正方体的正视图))
				int sum=1;
				for(int l=0;l<4;l++){//枚举每一面
					node tmp={a[i].c[l],a[i].c[(l-1+4)%4],a[j].c[(k+1-l+4)%4],a[j].c[(k+1-l-1+4)%4]};
					tmp=tmp.find_min();
					sum=sum*mp[tmp];
					mp[tmp]--;
					if(tmp.c[0]==tmp.c[2]&&tmp.c[1]==tmp.c[3])sum*=2;
                    if(tmp.c[0]==tmp.c[1]&&tmp.c[1]==tmp.c[2]&&tmp.c[2]==tmp.c[3])sum*=2;
				}
				ans+=sum;
				for(int l=0;l<4;l++){//枚举每一面
					node tmp={a[i].c[l],a[i].c[(l-1+4)%4],a[j].c[(k+1-l+4)%4],a[j].c[(k+1-l-1+4)%4]};
					tmp=tmp.find_min();
					mp[tmp]++;
				}
			}
			mp[a[i]]++,mp[a[j]]++;
		}
	}
	cout<<(ans/3);
}