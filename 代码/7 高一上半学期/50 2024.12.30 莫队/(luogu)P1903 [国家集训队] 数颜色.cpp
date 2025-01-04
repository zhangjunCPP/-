#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int block;
int col[N];
struct node{
	int l,r,id,tim;
	bool operator<(const node&oth)const{
		if(l/block==oth.l/block){
			if(r/block==oth.r/block)return ((r/block)&1)?tim<oth.tim:tim>oth.tim;
			return r<oth.r;
		}
		return l<oth.l;
	}
}q[N];
struct node2{
	int pos,color;
}p[N];
int cnt1,cnt2;
int ans[N];
int sum[N],tot;
void add(int x){if(!sum[x])tot++;sum[x]++;}
void del(int x){sum[x]--;if(!sum[x])tot--;}
void move(int x,int id){
	if(p[x].pos>=q[id].l&&p[x].pos<=q[id].r){
		sum[col[p[x].pos]]--;if(!sum[col[p[x].pos]])tot--;
		if(!sum[p[x].color])tot++;sum[p[x].color]++;
	}
	swap(col[p[x].pos],p[x].color);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr),cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	block=pow(n,2.0/3.0);
	for(int i=1;i<=n;i++)cin>>col[i];
	for(int i=1;i<=m;i++){
		char s;
		int l,r;
		cin>>s>>l>>r;
		if(s=='Q')q[++cnt1]={l,r,cnt1,cnt2};
		else p[++cnt2]={l,r};
	}
	sort(q+1,q+cnt1+1);
	int L=1,R=0;
	int Time=0;
	for(int i=1;i<=cnt1;i++){
		while(L>q[i].l)add(col[--L]);
		while(R<q[i].r)add(col[++R]);
		while(L<q[i].l)del(col[L++]);
		while(R>q[i].r)del(col[R--]);
		while(Time<q[i].tim)move(++Time,i);
		while(Time>q[i].tim)move(Time--,i);
		ans[q[i].id]=tot;
	}
	for(int i=1;i<=cnt1;i++)cout<<ans[i]<<"\n";
}