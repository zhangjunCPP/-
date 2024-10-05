#include<bits/stdc++.h>
namespace IO{
    template<typename T>
    void read(T &x){
        char ch=getchar();int fl=1;x=0;
        while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getchar();}
        while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getchar();}
        x*=fl;
    }
    template<typename T,typename ...Args>
    void read(T &x,Args& ...args){
        read(x);read(args...);
    }
    template <typename _Tp>
    void write(_Tp x) {
        if(x<0) x=(~x+1),putchar('-');
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
}
using namespace std;
using namespace IO;
const int N=2e6+5,mod=1e9+7;
int n,f[N][3],ch[N][2],a[N],L[N],R[N],rt,Lv[N],Rv[N],Ans=0;
string s;
void build(int x,int l,int r) {
    if(!x) return ;
    Lv[x]=l; Rv[x]=r;
    build(L[x],l,x); build(R[x],x,r);
}
void dfs(int x) {
    f[x][0]=f[x][1]=f[x][2]=0;
    if(!x) return ;
    dfs(L[x]); dfs(R[x]);
    int l=L[x],r=R[x];
    //钦定不选
    Ans=max(Ans,f[l][1]+f[r][0]);
    f[x][0]=f[l][0]; f[x][1]=f[r][1]; f[x][2]=f[l][0]+f[r][1];
    if(x==rt) return ;
    if(s[x]!='R') {
        f[x][2]=max(f[x][2],f[r][2]+1);
        f[x][2]=max(f[x][2],f[l][1]+f[r][1]+1);
        f[x][0]=max(f[x][0],max(f[l][1],f[r][0])+1);
        Ans=max({Ans,f[l][2]+1,f[l][0]+f[r][0]+1});
    }
    if(s[x]!='L') {
        f[x][2]=max(f[x][2],f[l][2]+1);
        f[x][2]=max(f[x][2],f[l][0]+f[r][0]+1);
        f[x][1]=max(f[x][1],max(f[l][1],f[r][0])+1);
        Ans=max({Ans,f[r][2]+1,f[l][1]+f[r][1]+1});
    }
}
signed main() {
    freopen("chenqiao.in", "r", stdin);
	freopen("chenqiao.out", "w", stdout);
    int Test; read(Test);
    while(Test--) {
        stack<int> stk; 
        read(n);
        for(int i=1;i<=n;i++) {
            read(a[i]);
            L[i]=R[i]=0;
        }
        cin>>s; s=' '+s; Ans=0;
        for(int i=1;i<=n;i++) {
            if(stk.empty()) {
                rt=i;
                stk.push(i);
                continue;
            }
            while(!stk.empty() && a[i]>a[stk.top()]) {
                L[i]=stk.top();
                stk.pop();
            }
            if(stk.empty()) rt=i;
            if(!stk.empty()) R[stk.top()]=i;
            stk.push(i);
        }
        int flg=1;
        build(rt,0,n+1);
        for(int i=1;i<=n;i++) {
            if(i==rt) continue;
            if(Lv[i]==0) {
                if(s[i]=='L') {flg=0; break;}
                s[i]='R';
            }
            if(Rv[i]==n+1) {
                if(s[i]=='R') {flg=0; break;}
                s[i]='L';
            }
        }
        // cout<<s<<endl;
        if(!flg) {
            printf("-1\n");
            continue;
        }
        dfs(rt);
        write(Ans); putchar('\n');
    }
    return 0;
}
/*
1
4
4 1 3 2
????
*/
