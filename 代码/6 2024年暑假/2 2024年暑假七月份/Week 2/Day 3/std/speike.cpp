#include <bits/stdc++.h>
using namespace std;

const int MX = 500005;
const int INF = 1000000000;

template <typename T>
void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-')
        f = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f)
        x = -x;
}

struct NODE {
    int x, y, d;

    // NODE(const int &x0 = 0, const int &y0 = 0, const int &d0 = 0) : x(x0), y(y0), d(d0) {}

    bool operator<(const NODE &t) const { return y < t.y; }
};

struct REC {
    int x_0, x_1, y_0, y_1;

    REC(const int &l0 = 0, const int &r0 = 0, const int &d0 = 0, const int &u0 = 0)
        : x_0(l0), x_1(r0), y_0(d0), y_1(u0) {}

    void adjust() {
        if (x_0 > x_1)
            swap(x_0, x_1);
        if (y_0 > y_1)
            swap(y_0, y_1);
    }

    bool operator<(const REC t) const { return x_0 < t.x_0; }
};

int n, tx, ty;
REC a[MX];

void input() {
    read(n);
    read(tx), ty = 0;
    for (int i = 1; i <= n; i++) {
        read(a[i].x_0), read(a[i].y_0);
        read(a[i].x_1), read(a[i].y_1);
        a[i].adjust();
    }
}

int dis(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }

int calc() {
    set<NODE> st;
    sort(a + 1, a + n + 1);
	// for(int i=1;i<=n;i++) {
		// cout<<obs[i].l<<" "<<obs[i].d<<" "<<obs[i].r<<" "<<obs[i].u<<"\n";
	// }
    st.insert({0, 0, 0});
    for (int i = 1; i <= n; i++) {
        int Minl = INF, Minr = INF;
        auto L = st.lower_bound({a[i].x_0, a[i].y_0, 0});
        auto R = st.upper_bound({a[i].x_0, a[i].y_1, 0});
        while (L != R) {
            Minl = min(Minl, dis(L->x, L->y, a[i].x_0, a[i].y_0) + L->d);
            Minr = min(Minr, dis(L->x, L->y, a[i].x_0, a[i].y_1) + L->d);
            st.erase(L++);
        }
        st.insert({a[i].x_0, a[i].y_0, Minl});
        st.insert({a[i].x_0, a[i].y_1, Minr});
        // cout<<obs[i].x_0<<" "<<obs[i].y_0<<" "<<obs[i].y_1<<" "<<Minl<<" "<<Minr<<"\n";
    }
    int ret = INF;
    for (set<NODE>::iterator it = st.begin(); it != st.end(); it++){
    	        ret = min(ret, dis(it->x, it->y, tx, ty) + it->d);
		// cout<<it->x<<" "<<it->y<<" "<<it->d<<"\n";
    }
    cerr << ret << endl;
    return ret;
}

void work() { printf("%d\n", calc()); }

int main() {
    // freopen("speike.in", "r", stdin);
    // freopen("speike.out", "w", stdout);
    input();
    work();
    return 0;
}
