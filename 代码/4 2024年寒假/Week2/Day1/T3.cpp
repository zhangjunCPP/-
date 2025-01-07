/*
 * 什么鬼？
 *
 * 题目大意懂了。
 * 好像只有最后两行有用，其他都是废话。
 *
 * 至于这个非简要题意，我实在是没看懂。
 * 好像可以直接从最后两行入手，直接构造出答案？？
 *
 * 我们如果采用一行一行的构造，那么应该能选出 k 个数使 max(|a_i1-a_i2|,|b_i1,b_i2|)=1 满足。
 * 同时，由于我们是选的同一行，因此能让 a_i_j-a_i_{j-1}=a_i_{j-1}-a_i_{j-2} 满足。
 * 那么我们就必须让 b_i_j-b_i_{j-1}=b_i_{j-1}-b_i_{j-2} 不满足。
 * 这似乎挺简单的，我们让第一个间距设为1，第二个间距设为2，两个交替。
 * 同时，如果两个直接间距为2，那么 max(|a_i1-a_i2|,|b_i1,b_i2|)=1 都满足不了。
 *
 * 似乎就完了？
 * 正确性存疑。
 *
 * 实现？
 * ？？？？
 * 去开了个大，顿悟，好像这样做就是对的。
 *
 * 实现的话可以考虑将棋盘以两个点作为一个整体，黑白染色。
 * 然后将黑色的点记为集合A，白色为B，每次取一个A，一个B。
 *
 * 为了确保正确性，可以将 1~500 的点全部染色，反正也不会挂。
 *
 * 输出一下，发现能保证间距1，2交替。
 * -----------
 * 特别的，当 min(n,m)<k 时，可以全部输出，这个手摸一下就知道了。
 *
 * 而且，经过我们的分析，当选出的点只能覆盖一个间距时无解，即只有 k<=2 无解。
 *
 * 水题。
 *
 * 难道我真的是天才？
 */

#include <bits/stdc++.h>

using namespace std;
const int N=505;
int mp[N][N];
pair<int,int> A[N*N],B[N*N];
int cnt1,cnt2;
int main() {
//	freopen("T3.in","r",stdin);
//	freopen("T3.out","w",stdout);
	int n,m,k;
	cin>>n>>m>>k;
	if(min(n,m)<k){
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cout<<i<<" "<<j<<"\n";
		return 0;
	}
	if(k<=2) {puts("-1");return 0;}
	for(int i=1;i<=500;i++) for(int j=1+2*(i&1);j<=500;j+=4)mp[i][j]=mp[i][j+1]=1;//以两个点为整体黑白染色。
//	for(int i=1;i<=n;i++){
//		for (int j=1;j<=m;j++)cout<<mp[i][j]<<" ";
//		cout<<"\n";
//	}
//	cout<<"-------\n";
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]) A[++cnt1]={i,j};
			else B[++cnt2]={i,j};
		}
	}
	while(cnt1&&cnt2){
		cout<<A[cnt1].first<<" "<<A[cnt1].second<<"\n";cnt1--;
		cout<<B[cnt2].first<<" "<<B[cnt2].second<<"\n";cnt2--;
	}
	if(cnt1)cout<<A[cnt1].first<<" "<<A[cnt1].second<<"\n";cnt1--;
	if(cnt2)cout<<B[cnt2].first<<" "<<B[cnt2].second<<"\n";cnt2--;
}