#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef unsigned ui;
struct node1 {bool len; ui l0c, l0l, l1c, l1l, rc, rl0, rl1;};
const node1 N1[4] = {
	{0, 0, 1, 0, 1, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0},
	{1, 1, 1, 0, 1, 0, 0, 1}
};
node1 operator + (const node1 &x, const node1 &y) {
	node1 ans;
	ans.len = x.len ^ y.len;
	if (y.len) {
		ans.l0c = y.l0c + x.l1c * y.l0l;
		ans.l0l = x.l1l * y.l0l;
		ans.l1c = y.l1c + x.l0c * y.l1l;
		ans.l1l = x.l0l * y.l1l;
	}
	else {
		ans.l0c = y.l0c + x.l0c * y.l0l;
		ans.l0l = x.l0l * y.l0l;
		ans.l1c = y.l1c + x.l1c * y.l1l;
		ans.l1l = x.l1l * y.l1l;
	}
	ans.rc = x.rc + y.rc + x.l0c * y.rl0 + x.l1c * y.rl1;
	if (x.len) {
		ans.rl0 = x.rl0 + x.l1l * y.rl1;
		ans.rl1 = x.rl1 + x.l0l * y.rl0;
	}
	else {
		ans.rl0 = x.rl0 + x.l0l * y.rl0;
		ans.rl1 = x.rl1 + x.l1l * y.rl1;
	}
	return ans;
}
struct node2 {ui mtx[6][4];};
const node2 N2[4] = {
	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}
};
node2 operator + (const node2 &x, const node2 &y) {
	node2 ans; memset(ans.mtx, 0, sizeof ans.mtx);
	for (int i = 0; i < 3; i++) {
		ans.mtx[i][0] = y.mtx[i][0] + x.mtx[0][0] * y.mtx[i][1] + x.mtx[1][0] * y.mtx[i][2] + x.mtx[2][0] * y.mtx[i][3];
		ans.mtx[i][1] = x.mtx[0][1] * y.mtx[i][1] + x.mtx[1][1] * y.mtx[i][2] + x.mtx[2][1] * y.mtx[i][3];
		ans.mtx[i][2] = x.mtx[0][2] * y.mtx[i][1] + x.mtx[1][2] * y.mtx[i][2] + x.mtx[2][2] * y.mtx[i][3];
		ans.mtx[i][3] = x.mtx[0][3] * y.mtx[i][1] + x.mtx[1][3] * y.mtx[i][2] + x.mtx[2][3] * y.mtx[i][3];
	}
	for (int i = 3; i < 6; i++) {
		ans.mtx[i][0] = x.mtx[i][0] + y.mtx[i][0] + x.mtx[0][0] * y.mtx[i][1] + x.mtx[1][0] * y.mtx[i][2] + x.mtx[2][0] * y.mtx[i][3];
		ans.mtx[i][1] = x.mtx[i][1] + x.mtx[0][1] * y.mtx[i][1] + x.mtx[1][1] * y.mtx[i][2] + x.mtx[2][1] * y.mtx[i][3];
		ans.mtx[i][2] = x.mtx[i][2] + x.mtx[0][2] * y.mtx[i][1] + x.mtx[1][2] * y.mtx[i][2] + x.mtx[2][2] * y.mtx[i][3];
		ans.mtx[i][3] = x.mtx[i][3] + x.mtx[0][3] * y.mtx[i][1] + x.mtx[1][3] * y.mtx[i][2] + x.mtx[2][3] * y.mtx[i][3];
	}
	return ans;
}
char str[MAXN];
namespace sgt {
	node1 val[MAXN << 2][2][2]; node2 val2[MAXN << 2][2]; bool tag[MAXN << 2];
	void addtag(int rt) {
		tag[rt] ^= 1; for (int _ : {0, 1}) swap(val[rt][0][_], val[rt][1][_]); swap(val2[rt][0], val2[rt][1]);
	}
	void pushdown(int rt) {if (tag[rt]) addtag(rt << 1), addtag(rt << 1 | 1), tag[rt] = 0;}
	void pushup(int rt) {
		for (int _ : {0, 1}) for (int __ : {0, 1}) {
			val[rt][_][__] = val[rt << 1][_][__] + val[rt << 1 | 1][_][__];
		}
		for (int _ : {0, 1}) val2[rt][_] = val2[rt << 1][_] + val2[rt << 1 | 1][_];
	}
	void build(int rt, int l, int r) {
		if (l == r) {
			if (str[l] == '*') val[rt][0][0] = val[rt][0][1] = N1[3], val2[rt][0] = N2[3];
			else if (str[l] == 'A') val[rt][0][0] = N1[1], val[rt][0][1] = N1[2], val2[rt][0] = N2[1];
			else val[rt][0][0] = N1[2], val[rt][0][1] = N1[1], val2[rt][0] = N2[2];
			val[rt][1][0] = val[rt][1][1] = N1[0]; val2[rt][1] = N2[0]; return;
		} int mid = (l + r) >> 1; build(rt << 1, l, mid); build(rt << 1 | 1, mid + 1, r); pushup(rt);
	}
	void modify(int rt, int l, int r, int x) {
		if (l == r) {
			if (str[l] == '*') val[rt][0][0] = val[rt][0][1] = N1[3], val2[rt][0] = N2[3];
			else if (str[l] == 'A') val[rt][0][0] = N1[1], val[rt][0][1] = N1[2], val2[rt][0] = N2[1];
			else val[rt][0][0] = N1[2], val[rt][0][1] = N1[1], val2[rt][0] = N2[2];
			val[rt][1][0] = val[rt][1][1] = N1[0]; val2[rt][1] = N2[0];
			if (tag[rt]) addtag(rt), tag[rt] = 1; return;
		} int mid = (l + r) >> 1; pushdown(rt);
		x <= mid ? modify(rt << 1, l, mid, x) : modify(rt << 1 | 1, mid + 1, r, x); pushup(rt);
	}
	void modify(int rt, int l, int r, int x, int y) {
		if (x <= l && r <= y) return addtag(rt); int mid = (l + r) >> 1; pushdown(rt);
		if (x <= mid) modify(rt << 1, l, mid, x, y); if (y > mid) modify(rt << 1 | 1, mid + 1, r, x, y); pushup(rt);
	}
	void query(int rt, int l, int r, int x, int y, node1 &ans1, node1 &ans2, node2 &ans3) {
		if (x <= l && r <= y) return ans1 = ans1 + val[rt][0][0], ans2 = ans2 + val[rt][0][1], ans3 = ans3 + val2[rt][0], void();
		int mid = (l + r) >> 1; pushdown(rt); if (x <= mid) query(rt << 1, l, mid, x, y, ans1, ans2, ans3);
		if (y > mid) query(rt << 1 | 1, mid + 1, r, x, y, ans1, ans2, ans3);
	}
}
int main() {

	int n, q; scanf("%d", &n); scanf("%s", str + 1);
	sgt::build(1, 1, n); scanf("%d", &q); while (q--) {
		int x, y, z; char ch; scanf("%d %d", &x, &y);
		if (x == 1) {
			scanf("%d", &z);
			node1 f = N1[0], g = N1[0]; node2 h = N2[0];
			sgt::query(1, 1, n, y, z, f, g, h);
			printf("%u %u %u 0\n", h.mtx[3][0] + f.rc + g.rc, h.mtx[4][0] - f.rc, h.mtx[5][0] - g.rc);
		}
		else if (x == 2) getchar(), str[y] = getchar(), sgt::modify(1, 1, n, y);
		else scanf("%d", &z), sgt::modify(1, 1, n, y, z);
	}
}