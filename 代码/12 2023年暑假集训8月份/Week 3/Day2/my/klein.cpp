/*
空间极小
考虑暴力
肯定不能建边
1e6的空间 可以过
那最简单的就是直接floyed
---------- 
O(1)
我们发现，对于竖着的，其实是两两连成环
对于横着的，它自己就是一个环
因此，问题的关键就是解决竖着的
-----
直接乱搞 
*/ 
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
int abs_s(int x){return x<0?-x:x;}
int n,q;
int u_1,v_1,u_2,v_2;
int ans,ans1,ans2,ans3,ans4;
int main(){
	freopen("klein.in","r",stdin);
	freopen("klein.out","w",stdout); 
	n=read();
	q=read();
	while(q--){
		u_1=read();v_1=read();u_2=read();v_2=read();
		
		ans1=abs_s(u_1-u_2)+abs_s(v_1-v_2);
		ans2=abs_s(u_1-u_2)+abs_s( (n+1) - abs_s(v_1-v_2) );
		ans3=abs_s( (n+1) - abs_s(u_1-u_2) )+abs_s(v_1+v_2-n);
		ans4=abs_s( (n+1) - abs_s(u_1-u_2) )+abs_s( (n+1) - abs_s(v_1+v_2-n) );
		
		ans=min({ans1,ans2,ans3,ans4});
		
		printf("%d\n",ans);
	}

	return 0;
}

