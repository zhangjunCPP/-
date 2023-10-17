#include <bits/stdc++.h>
#define int long long
const int N=1e7+10;
using namespace std;
int read(){
    int x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
int n;
int p[N];
int ls[N],rs[N];
int q[N],top;
void build(){
    top=1;
    q[1]=1;
    for(int i=2;i<=n;i++){
        while(top&&p[q[top]]>p[i]) top--;
        if(!top)ls[i]=q[1];
        else ls[i]=rs[q[top]],rs[q[top]]=i;
        q[++top]=i;
    }
}
signed main(){
    n=read();
    for(int i=1;i<=n;i++) p[i]=read();
    build();
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++){
        ans1=ans1^(i*(ls[i]+1));
        ans2=ans2^(i*(rs[i]+1));
    }
    cout<<ans1<<" "<<ans2;
}