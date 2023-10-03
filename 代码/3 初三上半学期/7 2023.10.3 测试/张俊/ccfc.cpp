#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main(){
    freopen("ccfc.in","r",stdin);
    freopen("ccfc.out","w",stdout);
    string s;
    cin>>s;
    int len=s.length();
    for(int i=0;i<len;i++){
        int ans=0;
        int len2=1;
        for(int j=i;j<len&&len2*3<len-i;j++){
            bool flag1=true;
            for(int k=1;k<=len2;k++) {
                if(s[i+k-1]!=s[j+k]) {
                    flag1=false;
                    break;
                }
            }
            if(!flag1){
            	len2++;
            	continue;
			} 
            for(int k=1;k<=len2;k++){
                if(s[i+k-1]!=s[len-len2+k-1]) {
                    flag1=false;
                    break;
                }
            }
            if(flag1)ans++;
            len2++;
        }
        cout<<ans<<" ";
    }
}
