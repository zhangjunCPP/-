#include<bits/stdc++.h>
using namespace std;
string s[105];
int n,m;
bool check(int x,int y) {
	return (x>=0&&x<n&&y>=0&&y<m);
}
int dx[8]={-1,-1,-1,0,0,1,1,1};
int dy[8]={-1,0,1,-1,1,-1,0,1};
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			for(int k=0;k<8;k++) {
				int i1=i;
				int i2=i1+dx[k];
				int i3=i2+dx[k];
				int i4=i3+dx[k];
				int i5=i4+dx[k];
				int j1=j;
				int j2=j1+dy[k];
				int j3=j2+dy[k];
				int j4=j3+dy[k];
				int j5=j4+dy[k];
				if(check(i1,j1)&&check(i2,j2)&&check(i3,j3)&&check(i4,j4)&&check(i5,j5)&&s[i1][j1]=='s'&&s[i2][j2]=='n'&&s[i3][j3]=='u'&&s[i4][j4]=='k'&&s[i5][j5]=='e') {
					cout<<i1+1<<" "<<j1+1<<"\n";
					cout<<i2+1<<" "<<j2+1<<"\n";
					cout<<i3+1<<" "<<j3+1<<"\n";
					cout<<i4+1<<" "<<j4+1<<"\n";
					cout<<i5+1<<" "<<j5+1<<"\n";
					return 0;
				}
			}
		}
	}
}