/*
 * 由于树的形态是递归定义的，所以或许这道题与 $m$ 无关，可以直接计算？
 * 看了下样例，每次新增的直径都是同一个部分，所以好像确实可以直接计算？
 * 手摸一下。
 * 我们可不可以从每条边的贡献去考虑？
 *
 * 好像这么说不太恰当……但我也描述不来……
 *
 * 果然上厕所有用，CZC我爱你。
 *
 * ------------
 * 记每个点的子树第一大与第二大为 mx1,mx2。（第一大要加上自己）
 * 则答案为 max(mx1[1]*(2m-2)+mx1[i]+mx2[i])
 * 具体的方式放在图里了。
 */
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=2e5+10;
vector<int> G[N];
ull mx1[N],mx2[N];//子树第一大与第二大 （第一大要加上自己）
void dfs(int u){
    int Mx1=0,Mx2=0;
    for(int v:G[u]){
        dfs(v);
        if(mx1[v]>Mx1) Mx2=Mx1,Mx1=mx1[v];
        else if(mx1[v]>Mx2) Mx2=mx1[v];
    }
    mx1[u]=Mx1+1,mx2[u]=Mx2;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        G[x].push_back(i);
    }
    dfs(1);
    ull tmp=mx1[1];
    ull ans=tmp*m;
    for(int i=1;i<=n;i++) {
        if(mx2[i])ans=max(ans,tmp*(2*m-2)+mx1[i]+mx2[i]);
    }
    cout<<ans;
}

/*
input:
14 3
1
1
3
4
5
5
4
8
3
10
11
12
12
ans:
32

input:
4 5
1
2
3
ans:
20
 */