#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int p,s;
    cin>>p>>s;
    int MIN=1*(p/2-1);
    int MAX=(p/4)*(p/2-p/4);
    if(p&1||s<MIN||s>MAX) {puts("Impossible");return 0;}

    int x=p/2-1,y=1;
    if(x*y==s){
        putchar('2');putchar('3');
        for(int i=2;i<=x;i++) putchar('2');
        putchar('3');putchar('3');
        for(int i=2;i<=x;i++) putchar('2');
        return 0;
    }

    for(x--,y++;x>=y;x--,y++){
        if(x*y>=s){

            int more=s-x*(y-1);
            for(int i=1;i<=y;i++) putchar('2');
            putchar('3');
            for(int i=2;i<=more;i++) putchar('2');
            putchar('3');
            if(more!=x){
                putchar('1');
                for(int i=1;i<=x-more-1;i++) putchar('2');
                putchar('3');
                for(int i=3;i<=y;i++)putchar('2');
            }
            else for(int i=2;i<=y;i++) putchar('2');
            putchar('3');
            for(int i=2;i<=x;i++) putchar('2');
            return 0;
        }
    }
    puts("Impossible");
}