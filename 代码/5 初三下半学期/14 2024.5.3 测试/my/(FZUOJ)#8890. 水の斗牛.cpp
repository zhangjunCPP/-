#include<bits/stdc++.h>
using namespace std;
map<string,int> id;
map<int,string> rev;
map<char,int> decode;
int cnt;
int n;
struct node{
    struct node_1{int color,val;}card[6],boom,niu,tieban;
    //boom.color:有无炸弹,boom.val:炸弹点数
    //niu.color:有无牛,niu.val:分
    //tieban.color:有无铁板,tieban.val:铁板点数
    bool niuniu;
    //有无牛牛
}player[5];
int check(int x,int y){//返回x的胜利情况(-1/0/1)
    //check-boom
    if(player[x].boom.color&&player[y].boom.color){
        if(player[x].boom.val>player[y].boom.val)return 1;
        else if(player[x].boom.val<player[y].boom.val)return -1;
        else return 0;
    }
    else if(player[x].boom.color)return 1;
    else if(player[y].boom.color)return -1;
    //check-niuniu
    if(player[x].niuniu&&player[y].niuniu)return 0;
    else if(player[x].niuniu)return 1;
    else if(player[y].niuniu)return -1;
    //check-niu
    

}
void solve(){

}
int main(){
    // decode['a']=4,decode['b']=3,decode['c']=2,decode['d']=1;
    // int opt;
    // cin>>opt;
    // int T;
    // cin>>T>>n;
    // for(int i=1;i<=n;i++){
    //     string s;
    //     cin>>s;
    //     cnt++;
    //     id[s]=cnt;
    //     rev[cnt]=s;
    // }
    // while(T--)solve();
    int opt,T,n;
    cin>>opt>>T>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        cout<<s<<" 0\n";
    }
}