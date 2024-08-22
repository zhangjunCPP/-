#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int N = 500005;
int n,tot,idx,siz[N],fa[N],id[N],l[N],r[N];
char s[N],ans[N];
vector<int> e[N];
void get_siz(int u){
	siz[u] = 1;
	for(int v:e[u]) get_siz(v),siz[u] += siz[v];
}
void get_ans(int u,int st){
	int k = st+1;
	for(int v:e[u]){
		ans[k] = '(',ans[k+2*siz[v]-1] = ')';
		get_ans(v,k);
		k += 2*siz[v];
	}
}
int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin >> s+1;
	n = strlen(s+1);
	int las = 0,now = 0;
	l[1] = r[1] = tot = 1;
	for(int i=1;i<=n;i++){
		now = now+(s[i]==')');
		if(now > las){
			tot++;
			l[tot] = r[tot] = i,las = 0,now = 1;
			for(int j=l[tot-1];j<=r[tot-1];j++) if(s[j] == '(') las++;
		}else{
			r[tot] = i;
		}
	}
	for(int i=1;i<=n;i++) if(s[i]=='(') id[i] = ++idx;
	for(int i=1,k=0;i<=tot;i++){
		for(int j=l[i];j<=r[i];j++){
			if(s[j]==')') {
				k++;
				continue;
			}
			fa[id[j]] = k;
		}
		for(int j=l[i];j<=r[i];j++) if(s[j]=='(') {
			k = id[j]-1;
			break;
		}
	}
	for(int i=1;i<=idx;i++) e[fa[i]].pb(i);
	for(int i=0;i<=idx;i++) reverse(e[i].begin(),e[i].end());
	get_siz(0),get_ans(0,0);
	for(int i=1;i<=n;i++) cout << ans[i];
	return 0;
}