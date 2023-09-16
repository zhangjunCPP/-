//Author:hos_lyric
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) {
	return os << "(" << a.first << ", " << a.second << ")";
};

template <class T> void pv(T a, T b) {
	for (T i = a; i != b; ++i)
		cerr << *i << " ";
	cerr << endl;
}

template <class T> bool chmin(T &t, const T &f) {
	if (t > f) {
		t = f;
		return true;
	}
	return false;
}

template <class T> bool chmax(T &t, const T &f) {
	if (t < f) {
		t = f;
		return true;
	}
	return false;
}


constexpr int INF = 1001001001;


int bitN;
vector<pair<int, int>> bit;

void init(int bitN_) {
	bitN = bitN_;
	bit.assign(bitN, make_pair(INF, -1));
}

void update(int pos, const pair<int, int> &val) {
	for (int x = pos; x < bitN; x |= x + 1) {
		chmin(bit[x], val);
	}
}

pair<int, int> get(int pos) {
	pair<int, int> ret(INF, -1);
	for (int x = pos - 1; x >= 0; x = (x & (x + 1)) - 1) {
		chmin(ret, bit[x]);
	}
	return ret;
}


int N;
vector<int> A;

struct Entry {
	int x, y, side, id;
};

ostream &operator<<(ostream &os, const Entry &e) {
	return os << "(" << e.x << "," << e.y << ";" << e.side << ";" << e.id << ")";
}
vector<Entry> es;

vector<int> three;

void dfs(int side, int i, int id, int s0, int s1, int s2) {
	const int begin = side ? (N / 2) : 0;
	const int end = side ? N : (N / 2);
	if (i == end) {
		if (s0 <= s1 && s1 <= s2) {
			int x = s1 - s0, y = s2 - s1;
			if (side) {
				swap(x, y);
			}
			es.push_back(Entry{x, y, side, id});
		}
	} else {
		dfs(side, i + 1, id, s0 + A[i], s1, s2);
		dfs(side, i + 1, id + three[i - begin], s0, s1 + A[i], s2);
		dfs(side, i + 1, id + 2 * three[i - begin], s0, s1, s2 + A[i]);
	}
}

int main() {
	
	freopen("treasure.in","r",stdin);
	freopen("treasure.out","w",stdout);
	for (; ~scanf("%d", &N); ) {
		A.resize(N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", &A[i]);
		}

		three.resize(N - N / 2 + 1);
		three[0] = 1;
		for (int i = 1; i < (int)three.size(); ++i) {
			three[i] = three[i - 1] * 3;
		}
		es.clear();
		dfs(0, 0, 0, 0, 0, 0);
		dfs(1, N / 2, 0, 0, 0, 0);
// cerr<<"es = ";pv(es.begin(),es.end());

		int opt = INF;
		int id0 = 0, id1 = 0;

		vector<int> xs, ys, zs;
		for (const Entry &e : es) {
			xs.push_back(e.x);
			ys.push_back(e.y);
			zs.push_back(-(e.x + e.y));
		}
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());
		sort(zs.begin(), zs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());
		zs.erase(unique(zs.begin(), zs.end()), zs.end());
// cerr<<"xs = ";pv(xs.begin(),xs.end());
// cerr<<"ys = ";pv(ys.begin(),ys.end());
// cerr<<"zs = ";pv(zs.begin(),zs.end());

		// x <= X && y <= Y
		// x >= X && y >= Y
		// y <= Y && z <= Z
		// y >= Y && z >= Z
		// z <= Z && x <= X
		// z >= Z && x >= X
		for (int h = 0; h < 6; ++h) {
			switch (h) {
				case 0:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						return ((e0.x != e1.x) ? (e0.x < e1.x) : (e0.side < e1.side));
					});
					break;
				case 1:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						return ((e0.x != e1.x) ? (e0.x > e1.x) : (e0.side < e1.side));
					});
					break;
				case 2:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						return ((e0.y != e1.y) ? (e0.y < e1.y) : (e0.side < e1.side));
					});
					break;
				case 3:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						return ((e0.y != e1.y) ? (e0.y > e1.y) : (e0.side < e1.side));
					});
					break;
				case 4:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						const int z0 = -(e0.x + e0.y);
						const int z1 = -(e1.x + e1.y);
						return ((z0 != z1) ? (z0 < z1) : (e0.side < e1.side));
					});
					break;
				case 5:
					sort(es.begin(), es.end(), [&](const Entry & e0, const Entry & e1) -> bool {
						const int z0 = -(e0.x + e0.y);
						const int z1 = -(e1.x + e1.y);
						return ((z0 != z1) ? (z0 > z1) : (e0.side < e1.side));
					});
					break;
				default:
					assert(false);
			}
// cerr<<"h = "<<h<<endl;
// cerr<<"  es = ";pv(es.begin(),es.end());
			init((h < 2) ? ys.size() : (h < 4) ? zs.size() : xs.size());
			for (const Entry &e : es) {
				int pos;
				int val;
				if (h < 2) {
					pos = lower_bound(ys.begin(), ys.end(), e.y) - ys.begin();
					val = -(e.x + e.y);
				} else if (h < 4) {
					pos = lower_bound(zs.begin(), zs.end(), -(e.x + e.y)) - zs.begin();
					val = e.x;
				} else {
					pos = lower_bound(xs.begin(), xs.end(), e.x) - xs.begin();
					val = e.y;
				}
				if (h & 1) {
					pos = bitN - 1 - pos;
					val = -val;
				}
				if (e.side) {
					const auto res = get(pos + 1);
					if (~res.second && chmin(opt, res.first - val)) {
						id0 = res.second;
						id1 = e.id;
					}
				} else {
					update(pos, make_pair(val, e.id));
				}
			}
		}

		vector<int> ans(N, -1);
		for (int i = 0; i < N / 2; ++i)
			ans[i] = id0 / three[i] % 3;
		for (int i = N / 2; i < N; ++i)
			ans[i] = 2 - id1 / three[i - N / 2] % 3;

		for (int i = 0; i < N; ++i) {
			if (i)
				printf(" ");
			printf("%d", ans[i] + 1);
		}
		puts("");

#ifdef LOCAL
		vector<int>sums(1 << N, 0);
		for (int i = 0; i < N; ++i)
			for (int p = 0; p < 1 << i; ++p)
				sums[p | 1 << i] = sums[p] + A[i];
		int brt = INF;
		for (int p = 0; p < 1 << N; ++p) {
			for (int q = p;; --q &= p) {
				int ss[3] = {sums[q], sums[p ^ q], sums[((1 << N) - 1)^p]};
				sort(ss, ss + 3);
				chmin(brt, ss[2] - ss[0]);
				if (!q)
					break;
			}
		}
		cerr << "brt = " << brt << endl;
		{
			int ss[3] = {};
			for (int i = 0; i < N; ++i)
				ss[ans[i]] += A[i];
			sort(ss, ss + 3);
			cerr << "ss = ";
			pv(ss, ss + 3);
			assert(opt == ss[2] - ss[0]);
			assert(brt == ss[2] - ss[0]);
		}
#endif
	}
	return 0;
}
