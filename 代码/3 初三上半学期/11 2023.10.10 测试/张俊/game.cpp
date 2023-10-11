/*
如果场上还有边删了仍然保持联通，那么肯定删那条。
也就是说，一个人输的时候，一定是一棵树的形式
去上了个厕所，有了点思路。
由于一个人输的时候图一定是树的形式，所以另外一个人就一定会把多余的边删掉 
因此，双方可以规定一棵树，两个人都把多余的边删掉，看谁先删完。
现在问题就是：如果一个人提前删了树上的点，会有什么影响？

不会 
*/ 

#include<bits/stdc++.h>
using namespace std;

void solve(){
	int n,m,k;
	cin>>n>>m>>k;
	string s;
	cin>>s;
	int len=s.size();
	for(int i=1;i<=m;i++) {
		int tmp;
		cin>>tmp>>tmp;
	}
	int last=m-(n-1);
	char ans;
	bool flag=false;
	while(true){
		for(int i=0;i<len;i++) {
			m--;
			if(m<0) {
				ans=s[i];
				flag=true;
				break;
			}
		}
		if(flag) break;
	}
	if(ans=='P') puts("G");
	else puts("P");
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int T;
	cin>>T;
	while(T--) solve(); 

	return 0;
}
