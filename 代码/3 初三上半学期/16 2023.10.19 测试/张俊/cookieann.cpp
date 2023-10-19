#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
void solve(){
	deque<int> q1,q2;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	
	int Begin=1,End=n;
	bool ans1=true;
	q1.push_back(a[1]);
	Begin=2;
	while(Begin<=End){
		int fir=q1.front(),sec=q1.back();
		if(a[Begin]==fir-1) {
			q1.push_front(a[Begin]);
			Begin++;
			continue;
		}
		if(a[Begin]==sec+1) {
			q1.push_back(a[Begin]);
			Begin++;
			continue;
		}
		if(a[End]==fir-1) {
			q1.push_front(a[End]);
			End--;
			continue;
		}
		if(a[End]==sec+1) {
			q1.push_back(a[End]);
			End--;
			continue;
		}
		ans1=false;
		break;
	}
	
	Begin=1,End=n;
	bool ans2=true;
	q2.push_back(a[n]);
	End=n-1;
	while(Begin<=End){
		int fir=q2.front(),sec=q2.back();
		if(a[Begin]==fir-1) {
			q2.push_front(a[Begin]);
			Begin++;
			continue;
		}
		if(a[Begin]==sec+1) {
			q2.push_back(a[Begin]);
			Begin++;
			continue;
		}
		if(a[End]==fir-1) {
			q2.push_front(a[End]);
			End--;
			continue;
		}
		if(a[End]==sec+1) {
			q2.push_back(a[End]);
			End--;
			continue;
		}
		ans2=false;
		break;
	}
	
	if(ans1||ans2) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
}
int main(){
	freopen("cookieann.in","r",stdin);
	freopen("cookieann.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve(); 


	return 0;
}

