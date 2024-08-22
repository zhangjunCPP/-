#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
const int N = 2e6+555;
const ll inf = 1e18;
ll n,q,sum,s[N],tot[2],c[N],cnt,val[N*4],tag[N*4];
int a[3][N];
void build(int l,int r,int u){
	if(l==r){
		val[u] = c[l]*2-l-1ll*l*(l+1)/2-1ll*(tot[0]-l)*(tot[0]-l+1)/2;
		return ;
	}
	int mid = (l+r)>>1;
	build(l,mid,u*2),build(mid+1,r,u*2+1);
	val[u] = min(val[u*2],val[u*2+1]);
}
void pushdown(int u){
	if(tag[u]){
		val[u*2] += tag[u],val[u*2+1] += tag[u];
		tag[u*2] += tag[u],tag[u*2+1] += tag[u];
		tag[u] = 0;
	}
}
void upd(int l,int r,int u,int sl,int sr,int w){
	if(sl>r || l>sr) return ;
	if(sl<=l && r<=sr) {
		val[u] += w,tag[u] += w;
		return ;
	}
	int mid = (l+r)>>1;
	pushdown(u);
	upd(l,mid,u*2,sl,sr,w),upd(mid+1,r,u*2+1,sl,sr,w);
	val[u] = min(val[u*2],val[u*2+1]);
}
ll ask(int l,int r,int u,int sl,int sr){
	if(sl>r || l>sr) return inf;
	if(sl<=l && r<=sr) return val[u];
	pushdown(u);
	int mid = (l+r)>>1;
	return min(ask(l,mid,u*2,sl,sr),ask(mid+1,r,u*2+1,sl,sr));
}
int main(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin >> n >> q;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++) {
			char x;cin >> x;
			a[i][j] = (x == 'C');
			tot[a[i][j]]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(!a[1][i]) sum += i;
		if(!a[2][i]) sum += i;
	}
	for(int i=1;i<=n;i++) s[i] = (!a[1][i])+(!a[2][i]);
	for(int i=1;i<=n;i++) s[i] += s[i-1];
	for(int i=1;i<=n;i++) if(!a[2][i]) cnt++;
	for(int i=1,w;i<=n;i++){
		if(s[i]<=i) continue;
		c[0] += s[i]-i,c[1] += -1-s[i]+i;
		c[s[i]-i+1] += 1;
	}
	for(int i=1;i<=tot[0];i++) c[i] += c[i-1];
	for(int i=1;i<=tot[0];i++) c[i] += c[i-1];
	build(0,tot[0]/2,1);
	cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
	for(int i=1;i<=n;i++) s[i] -= i;
	for(int i=1;i<=q;i++){
		int t,x,y,d;
		cin >> t >> x >> y;
		if(t == 1){
			if(a[x][y] == a[x][y+1]) d = 0;
			else if(a[x][y] == 0) d = -1;
			else d = 1;
			if(d == 1){
				if(s[y]>=0) upd(0,tot[0]/2,1,0,s[y],2);
				s[y]++,sum--;
			}else if(d == -1){
				s[y]--,sum++;
				if(s[y]>=0) upd(0,tot[0]/2,1,0,s[y],-2);
			}
			swap(a[x][y],a[x][y+1]);
			cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
		}else{
			cnt -= (!a[2][y]);
			swap(a[1][y],a[2][y]);
			cnt += (!a[2][y]);
			cout << ask(0,tot[0]/2,1,max(0ll,tot[0]-n),cnt)+sum+cnt << '\n';
		}
	}
	return 0;
}