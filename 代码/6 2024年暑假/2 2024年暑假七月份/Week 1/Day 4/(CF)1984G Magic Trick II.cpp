#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
vector<pair<int,int>> ans;
void solve(){	
	ans.clear();
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	bool flag=true;
	for(int i=1;i<=n;i++)if(a[i]!=i){flag=false;break;}
	if(flag){cout<<n<<"\n0\n";return;}
	flag=true;
	for(int i=1;i<=n;i++)if((a[i]+1)%n!=a[i%n+1]%n){flag=false;break;}
	if(flag){
		cout<<n-1<<"\n"<<a[1]-1<<"\n";
		for(int i=1;i<=a[1]-1;i++)cout<<"1 2\n";
		return;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)if(a[j]>a[i])cnt++;
	if(n&1||!(cnt&1)){
		cout<<n-2<<"\n";
		if(n&1){
			for(int i=2;i<n;i++){
				while(a[1]!=i){
					ans.push_back({3,1});
					int tmp1=a[1],tmp2=a[2];
					for(int j=1;j<=n;j++)a[j]=a[j+2];
					a[n-1]=tmp1,a[n]=tmp2;
				}
				while(a[n]!=i-1){
					ans.push_back({2,3});
					int tmp1=a[n];
					for(int j=n;j>=3;j--)a[j]=a[j-1];
					a[2]=tmp1;
				}
			}
			ans.push_back({3,1});
		}
		else{
			for(int i=2;i<=n;i++){
				int id=0;
				for(int j=1;j<=n;j++)if(a[j]==i)id=j;
				if(id&1){
					while(a[1]!=i){
						ans.push_back({3,1});
						int tmp1=a[1],tmp2=a[2];
						for(int j=1;j<=n;j++)a[j]=a[j+2];
						a[n-1]=tmp1,a[n]=tmp2;
					}
					while(a[n]!=i-1){
						ans.push_back({2,3});
						int tmp1=a[n];
						for(int j=n;j>=3;j--)a[j]=a[j-1];
						a[2]=tmp1;
					}	
				}
				else{
					while(a[n]!=i){
						ans.push_back({3,1});
						int tmp1=a[1],tmp2=a[2];
						for(int j=1;j<=n;j++)a[j]=a[j+2];
						a[n-1]=tmp1,a[n]=tmp2;
					}
					while(a[n-1]!=i-1){
						ans.push_back({2,1});
						int tmp1=a[1];
						for(int j=1;j<n;j++)a[j]=a[j+1];
						a[n-1]=tmp1;
					}
				}
			}
		}
	}
	else{
		cout<<n-3<<"\n";
		while(a[n]!=n){
			int id=0;
			for(int i=1;i<=n;i++)if(a[i]==n)id=i;
			if(id<=2){
				ans.push_back({4,1});
				int tmp1=a[1],tmp2=a[2],tmp3=a[3];
				for(int i=1;i<=n;i++)a[i]=a[i+3];
				a[n-2]=tmp1,a[n-1]=tmp2,a[n]=tmp3;
			}
			else{
				ans.push_back({4,3});
				int tmp1=a[3];
				for(int i=3;i<n;i++)a[i]=a[i+1];
				a[n]=tmp1;
			}
		}
		for(int i=2;i<n;i++){
			while(a[n-1]!=i){
				ans.push_back({3,1});
				int tmp1=a[1],tmp2=a[2];
				for(int j=1;j<n;j++)a[j]=a[j+2];
				a[n-2]=tmp1,a[n-1]=tmp2;
			}
			while(a[n-2]!=i-1){
				ans.push_back({2,1});
				int tmp1=a[1];
				for(int j=1;j<n-1;j++)a[j]=a[j+1];
				a[n-2]=tmp1;
			}
		}
	}

	cout<<ans.size()<<"\n";
	for(auto i:ans)cout<<i.first<<" "<<i.second<<"\n";
	return;
}
int main(){
	int T;
	cin>>T;
	while(T--)solve();
}