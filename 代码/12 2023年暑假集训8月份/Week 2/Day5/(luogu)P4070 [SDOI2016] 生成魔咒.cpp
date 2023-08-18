#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
struct node{
    int ch[26];
    int len,link;
}sam[N];
long long ans=0;
int last=1,tot=1;//初始节点为1，link[1]=0;虚拟状态为0
void add(int c){
    int cur=++tot;
    sam[cur].len=sam[last].len+1;
    int p=last;
    while(p&&!sam[p].ch[c]) {
        sam[p].ch[c]=cur;
        p=sam[p].link;
    }
    if(!p) sam[cur].link=1;
    else {
        int q=sam[p].ch[c];
        if(sam[q].len==sam[p].len+1)sam[cur].link=q;
        else {
            int clone=++tot;
            sam[clone]=sam[q];
            sam[clone].len=sam[p].len+1;
            sam[q].link=sam[cur].link=clone;
            while(p&&sam[p].ch[c]==q){
                sam[p].ch[c]=clone;
                p=sam[p].link;
            }
        }
    }
    last=cur;
    ans+=sam[cur].len-sam[sam[cur].link].len;
}
signed main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++) add(s[i]-'a');
    cout<<ans<<"\n";
}