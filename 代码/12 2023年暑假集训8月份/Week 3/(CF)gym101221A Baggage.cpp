#include <bits/stdc++.h>
#define int long long
using namespace std;
void print(int x,int y,int add){cout<<x+add<<" to "<<y+add<<"\n";}
void solve(int n,int add){
    switch (n) {
        case 4:
            print(6, -1, add);
            print(3, 6, add);
            print(0, 3, add);
            print(7, 0, add);

            break;
        case 5:
            print(8, -1, add);
            print(3, 8, add);
            print(6, 3, add);
            print(0, 6, add);
            print(9, 0, add);
            break;
        case 6:
            print(10, -1, add);
            print(7, 10, add);
            print(2, 7, add);
            print(6, 2, add);
            print(0, 6, add);
            print(11, 0, add);
            break;
        case 7:
            print(8, -1, add);
            print(5, 8, add);
            print(12, 5, add);
            print(3, 12, add);
            print(9, 3, add);
            print(0, 9, add);
            print(13, 0, add);
            break;
        default:
            print(2*n-2,-1,add);
            print(3,2*n-2,add);
            solve(n-4,add+4);
            print(0,2*n-5,add);
            print(2*n-1,0,add);
    }
}
signed main(){
    int n;
    cin>>n;
    if(n==3){
        print(2, -1, 0);
        print(5, 2, 0);
        print(3, -3, 0);
    }
    else solve(n,0);
}