#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <array>
#include <cmath>

typedef long long ll;
typedef std::array<ll, 2> vec2;
ll k, x, y;
std::vector<vec2> ans;
int invx = 1, invy = 1, swp;
inline void fix(ll a, ll b)
{
    if((a + b) % k)
        return;
    while(a + b)
    {
        int px = std::min(k, a), py = k - px;
        ans.push_back({px, py}), a -= px, b -= py;
    }
    return;
}
ll fx, fy;
int main(void)
{
    freopen("nine.in","r",stdin);
    freopen("nine.out","w",stdout);
    scanf("%lld%lld%lld", &k, &x, &y), fx = x, fy = y;
    if(x < 0)
        x = -x, invx = -1;
    if(y < 0)
        y = -y, invy = -1;
    if(y > x)
        std::swap(x, y), swp = 1;
    if((x + y) % 2 == 1 && k % 2 == 0)
        return puts("-1"), 0;
    if((x + y) % k == 0)
        fix(x, y);
    else
    {
        if(x + y < k && (x + y) % 2)
            ans.push_back({-k, 0}), x += k;
        ll p = (x + y) / k;
        if(p == 0)
        {
            vec2 now({x, k - x});
            ll dlt = (x + y) / 2;
            now[0] -= dlt, now[1] += dlt;
            ans.push_back({x - now[0], y - now[1]}), x = now[0], y = now[1];
            fix(x, y);
        }
        else if(((p + 1) * k - (x + y)) % 2 == 0)
        {
            vec2 now({p * k - y, y});
            ll dlt = ((p + 1) * k - (x + y)) / 2;
            now[0] -= dlt, now[1] += dlt;
            ans.push_back({x - now[0], y - now[1]}), x = now[0], y = now[1];
            fix(x, y);
        }
        else
        {
            vec2 now({x, (p + 1) * k - x});
            ll dlt = (x + y - p * k) / 2;
            now[0] -= dlt, now[1] += dlt;
            ans.push_back({x - now[0], y - now[1]}), x = now[0], y = now[1];
            fix(x, y);
        }
    }
    for(auto &v : ans)
    {
        if(swp)
            std::swap(v[0], v[1]);
        v[0] *= invx, v[1] *= invy;
    }
    vec2 now({0, 0});
    printf("%d\n", (int)ans.size());
    for(auto v : ans)
    {
        ll len = std::abs(v[0]) + std::abs(v[1]);
        if(len != k || std::abs(v[0]) >= 2147483647ll || std::abs(v[1]) >= 2147483647ll)
            return fputs("F\n", stderr), 0;
        now[0] += v[0], now[1] += v[1];
        printf("%lld %lld\n", now[0], now[1]);
    }
    if(now[0] != fx || now[1] != fy)
        fputs("F\n", stderr);
    return 0;
}
