#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,M=165;
const int mod=998244353;
struct matrix{
    int a[M][M];
    matrix(){memset(a,0,sizeof a);}
    matrix operator*(const matrix &b) const{
        matrix tmp;
        for(int i=0;i<M;i++)for(int j=0;j<M;j++)for(int k=0;k<M;k++)tmp.a[i][j]=(tmp.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
        return tmp;
    }
};
matrix qpow(matrix x,int y){
    matrix ans;
    for(int i=0;i<M;i++) ans.a[i][i]=1;
    while(y){
        if(y&1) ans=ans*x;
        y>>=1;
        x=x*x;
    }
    return ans;
}
int trie[N][27],tot;
bool flag[N];
void insert(string s){
    int now=0;
    int siz=s.size();
    for(int i=0;i<siz;i++){
        if(!trie[now][s[i]-'a']) trie[now][s[i]-'a']=++tot;
        now=trie[now][s[i]-'a'];
    }
    flag[now]=true;
}
map<pair<int,int>,int> mp;
int num;
queue<pair<int,int> > q;
int get(pair<int,int> x){
    if(x.first>x.second) swap(x.first,x.second);
    if(!mp.count(x)) {
        mp[x]=num;
        q.push(x);
        return num++;
    }
    else return mp[x];
}
signed main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        string s;
        cin>>s;
        insert(s);
    }
    matrix ans;
    get({0,0});
    while(!q.empty()){
        auto now=q.front();
        q.pop();
        int id=get(now);
        int x=now.first,y=now.second;
        for(int i=0;i<=25;i++){
            int dx=trie[x][i],dy=trie[y][i];
            if(!dx||!dy) continue;
            ans.a[id][get({dx,dy})]++;
            if(flag[dx]) ans.a[id][get({0,dy})]++;
            if(flag[dy]) ans.a[id][get({dx,0})]++;
            if(flag[dx]&&flag[dy]) ans.a[id][get({0,0})]++;
        }
    }
    ans=qpow(ans,m);
    cout<<ans.a[0][0];
}