#include <bits/stdc++.h>
using namespace std;

#define MAXN 100050
#define MAXB 3200

#define int long long

int n,B,id[MAXN],d[MAXN],tmpd[MAXN],m[MAXN],tag[MAXB];
void init(){
    B = max(sqrt(n * __lg(n)),1.0);
    for(int i = 1;i <= n;i ++)id[i] = (i - 1) / B + 1;//,cout << id[i] << ' ';
    // cout << '\n';
}
struct tsk {
    int id, x, y;
    tsk() {}
    tsk(int id) {
        this->id = id;
        x = m[id];
        y = d[id]; 
    }
};
struct up {
    tsk que[MAXB>>3];
    int head = 0;
    void ins(int x) {
        tsk t0 = tsk(x);
        while (head >= 2) {
            if ((__int128)(t0.y - que[head].y) * (que[head].x - que[head-1].x) >= (__int128)(que[head].y - que[head-1].y) * (t0.x - que[head].x)) {
                head--;
            } else {
                break;
            }
        }
        // cout << head+1 << ":" << t0.x << ' ' << t0.y << '\n';
        que[++head] = t0;
    }
    int get(int x) {
        int l = 2,r = head;
        while(l <= r){
            int mid = (l + r) >> 1;
            // cout << (que[mid-1].x - que[mid].x) << ' ' << x << ' ' <<  (que[mid].y )<< ' '<< ( que[mid-1].y) << '\n';
            if((__int128)(que[mid-1].x - que[mid].x)*x>(__int128)(que[mid].y - que[mid-1].y)){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        // cout << r << ' ' << que[r].x << ' ' << que[r].y << '\n';
        return que[r].x * x + que[r].y;
    }
    void clear(){
        head = 0;
    }
} q[MAXB];
void m_m(int pos,int v){
    m[pos] = v;
    int b = id[pos];
    q[b].clear();
    for(int i = B * (b - 1) + 1;i <= min(n,B * b);i ++){
        q[b].ins(i);
    }
} 
void m_d(int pos,int v){
    int b = id[pos];
    for(int i = pos;i <= min(n,B * b);i ++){
        d[i] += v - tmpd[pos];
    }
    for(int i = b + 1;i <= id[n];i ++)tag[i] += v - tmpd[pos];
    tmpd[pos] = v;
    q[b].clear();
    for(int i = B * (b - 1) + 1;i <= min(n,B * b);i ++){
        q[b].ins(i);
    }
}
int q_ans(int v){
    int res = 2e18;
    for(int i = 1;i <= id[n];i ++)res = min(res,q[i].get(v)+tag[i]);
    return res;
}
signed main() {
    double nw = clock();
    int q;
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
	cin >> n >> q;
	for(int i = 1;i <= n;i ++)cin >> tmpd[i],d[i] = tmpd[i] + d[i-1];
    for(int i = 1;i <= n;i ++)cin >> m[i];
    init();
    for(int i = 1;i <= n;i ++)::q[id[i]].ins(i);
	while(q --){
        int opt,x,y,v;
        cin >> opt >> x >> y >> v;
        if(opt == 1)m_d(x,y);
        else m_m(x,y);
        cout << q_ans(v) << '\n';
    }
    cerr << (clock() - nw) / CLOCKS_PER_SEC << "s\n";
}