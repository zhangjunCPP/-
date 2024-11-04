#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int tot1[N],tot2[N];
int main(){
	freopen("duel.in","r",stdin);
	freopen("duel.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;){
		int j=i;
		while(a[j]==a[i])j++;
		j--;
		tot1[a[i]]=tot2[a[i]]=j-i+1;
		i=j+1;
	}
	int ans=n;
	int last=0;
	for(int i=1;i<=n;){
		int nex=i+tot1[a[i]]-1+1;
		int now=tot1[a[i]];
		int now2=tot2[a[nex]];
		if(nex>n){
			ans-=min(last,now2);
			break;
		}
		last+=now;
		int tmp=min(tot2[a[nex]],last);
		last-=tmp,tot2[a[nex]]-=tmp;
		ans-=tmp;
		i=nex;
	}
	cout<<ans;
}

/*

# CSP-S 2024

妈的，去年重庆分数线太高得不了一等，今年老子必须拿回来

## T1

排序后一段一段的考虑，后面一段攻击前面所有的

水题，白送100分

## T2

不是，还考物理啊，你甚至还跟我个提示

发现对于每个车，能检测到他的一定是某个区间。

那么这就是最小区间覆盖模板，贪心可以解决（完了，我不会）

那我们的首要任务就是求出这个区间

这用二分比较好求

那么只要会贪心就做完了

有点小细节，但问题不大

拿下两百分

等后面打完暴力对拍一下，希望不挂

## T3

容易想到DP连续颜色段，中间的贡献可以预处理出来

妈的不管了，就这样



# 老子不信今年重庆分数线还能有200分甚至更多，这他妈-S不是-J
*/