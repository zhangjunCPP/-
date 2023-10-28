#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],b[N],c[N];
int u[N],v[N];
signed main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<n;i++) {
		cin>>u[i]>>v[i];
	}
	int ans=n;
	for(int i=1;i<=n;i++) {
		int tmp=0;
		int now=max(b[i]+i*c[i],1ll);
		while(now<a[i]) {
			tmp++;
			now+=max(b[i]+(i+tmp)*c[i],1ll);
		}
		ans=max(ans,i+tmp);
	}
	cout<<ans;
}

/*

考试的最开始30分钟写完，一秒不差。

题目全都看懂了。

感觉这次的T1完全是CCF做慈善，白送100分。不像去年，T1还要用算法。

但后面的……有点问题。

# T1

lock.cpp lock.in lock.out

总方案数为 $10^5$ ,枚举每一种情况，在暴力判断是否符合

判断方式很简单：找出与最后的状态不同的位数，位数为1，说明只转动了1个，否则，就看转动的幅度是否相同即可。

时间复杂度： $O(10^5n)$

我真的是服了，我以为这n种情况必须采用相同的方式，调了我半个小时

# T2

看了看数据范围。

倒数第二档是经典的 $2\times 10^5$ ,由此推测，这一档的时间复杂度应为 $nlogn$。

但是最后一档就直接变成 $2\times 10^6$ ，如果仍是 $nlogn$，就显得不太合理了，更大的可能是 $n\sqrt n$。由此观之，可能是莫队算法。

并且看了看，这道题用莫队来做确实挺合理的。

那么，倒数第二档应该不是 $nlogn$ ，可能更高。

# T3

大模拟 or 数据结构？

题目都看了半天。

有点蒙。

拿部分分

# T4

拿部分分。


*/ 
