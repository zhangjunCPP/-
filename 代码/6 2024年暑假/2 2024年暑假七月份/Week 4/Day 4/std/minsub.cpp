#include <bits/stdc++.h>

using i64 = long long;

int main() {
	freopen("minsub.in", "r",stdin);
	freopen("minsub.out", "w",stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    
	int N;
	std::cin >> N;
    
	std::vector<int> A(N);
	for (int i = 0; i < N; i++) {
		std::cin >> A[i];
	}
    
	int L = A[0], R = A[0];
	int ans = 0;
	for (int i = 1; i < N; i++) {
		if (A[i] >= L) {
			ans++;
			std::tie(L, R) = std::make_pair(std::max(0, A[i] - R), A[i] - L);
		} else {
			L = 0;
			R = A[i];
		}
	}
    
	if (L == 0) {
		ans++;
	}
	std::cout << ans << "\n";
    
	return 0;
}