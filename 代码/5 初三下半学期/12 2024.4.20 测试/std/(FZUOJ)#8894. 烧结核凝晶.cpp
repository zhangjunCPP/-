#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>

constexpr int N = 100005;
constexpr long double eps = 1e-11;

int n, k;
int a[N], b[N];
long double c[N];

bool check(long double x) {
    for (int i = 1; i <= n; ++i) c[i] = a[i] - x * b[i];
    std::sort(c + 1, c + n + 1, std::greater<long double>());
    long double res = 0;
    for (int i = 1; i <= k; ++i) res += c[i];
    return res >= 0;
}

int main() {
	freopen("salt.in","r",stdin);
	freopen("salt.out","w",stdout); 
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) std::cin >> a[i] >> b[i];
    long double l = 0, r = 1;
    while (r - l > eps) {
        long double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid - eps;
    }
    std::cout << std::fixed << std::setprecision(15) << l << '\n';
    return 0;
}
