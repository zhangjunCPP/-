// #include <bits/stdc++.h>
// using namespace std;
// const int N=1e5+10;
// struct node {
// 	int x,y;
// 	char c;
// }a[N];
// bool cmp(const node&x,const node&y) {
// 	if(x.x==y.x)return x.y>y.y;
// 	return x.x<y.x;
// }
// signed main() {
// 	// freopen("a.in","r",stdin);
// 	// freopen("a.out","w",stdout);
// 	string s;
// 	cin>>s;
// 	int n=s.size();
// 	// for(int T=1;T<=10000;T++) {
// 	// 	// cout<<"T="<<T<<":";
// 	// 	memset(a,0,sizeof a);
// 	// 	int w=0;
// 	// 	for(int i=0;i<n;i++) {
// 	// 		a[i]={w,i,s[i]};
// 	// 		w+=s[i]=='('?1:-1;
// 	// 	}
// 	// 	sort(a,a+n,cmp);
// 	// 	string tmp;
// 	// 	for(int i=0;i<n;i++) {/*cout<<a[i].c;*/tmp.push_back(a[i].c);}
// 	// 	// cout<<"\n";
// 	// 	s=tmp;
// 	// 	if(s=="()(()((()(((())(((((()") {
// 	// 		cout<<"T="<<T<<" find ans";
// 	// 		return 0;
// 	// 	}
// 	// }
// 	int w=0;
// 	for(int i=0;i<n;i++) {
// 		a[i]={w,i,s[i]};
// 		w+=s[i]=='('?1:-1;
// 		cout<<w<<" ";
// 	}
// 	cout<<"\n";
// 	sort(a,a+n,cmp);
// 	string tmp;
// 	for(int i=0;i<n;i++)cout<<a[i].c;
// 	// ((((()))()(((()))))())(()((())()(((()(()()())))(()())))())()(((()(()(()()(()()())())(())(())))()()))
// 	// ()(()((()(((())(((((()((())()))(())((())())((())((()(())))))))()))(()()()(()))((())))))()())(())()()
//
// }
// /*
//  *
//  */
//
// /*
// 1 2 3 4 5 4 3 2 3 2 3 4 5 6 5 4 3 2 1 2 1 0 1 2 1 2 3 4 3 2 3 2 3 4 5 6 5 6 7 6 7 6 7 6 5 4 3 4 5 4 5 4 3 2 1 2 1 0 1 0
// 1 2 3 4 3 4 5 4 5 6 5 6 5 6 7 6 7 6 7 6 5 6 5 4 5 6 5 4 5 6 5 4 3 2 3 2 3 2 1 0
// (((()())((()(()((())((()))((()))(()(())()())()(((())(()())()()()()(((())))(()()))))((()))((())))))))
// */
// /*
// 1 0 1 2 1 2 3 4 3 4 5 6 7 6 5 6 7 8 9 10 11 10 11 12 13 12 11 12 11 10 9 10 11 10 9 10 11 12 11 10 11 10 9 10 11 12 11 1
// 0 11 12 13 12 13 14 13 12 11 10 9 8 7 6 7 6 5 4 5 6 5 6 5 6 5 6 7 6 5 4 5 6 7 6 5 4 3 2 1 2 1 2 1 0 1 2 1 0 1 0 1 0
// ((((()))()(((()))))())(()((())()(((()(()()())))(()())))())()(((()(()(()()(()()())())(())(())))()()))
// */
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node {
	int x,y;
	char c;
}a[N];
bool cmp(const node&x,const node&y) {
	if(x.x==y.x)return x.y>y.y;
	return x.x<y.x;
}
string s;
int n;
string t;
void dfs(int k) {
	if(k==n) {
		int sum=0;
		for(int i=0;i<n;i++) {
			a[i]={sum,i,t[i]};
			sum+=t[i]=='('?1:-1;
		}
		sort(a,a+n,cmp);
		string tmp;
		for(int i=0;i<n;i++)tmp.push_back(a[i].c);
		if(tmp==s){cout<<t;exit(0);}
		return;
	}
	t[k]='(';
	dfs(k+1);
	t[k]=')';
	dfs(k+1);
}
int main() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	cin>>s;
	n=s.size();
	t.resize(n);
	dfs(0);
}