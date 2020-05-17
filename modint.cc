#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <assert.h>
#include <utility>
#include <tuple>
#include <array>
#include <bitset>
#include <cstdlib>
#include <complex>

using int64 = long long;
using uint64 = unsigned long long;

using namespace std;

using F = tuple<int64, int64>;  // (分子, 分母)

#define uint64 int64

template <int64 M>
struct ModInt {
    int64 n;
    constexpr ModInt(const int64 n = 0) noexcept : n(n % M) {}
    constexpr ModInt operator+(const ModInt rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    constexpr ModInt operator-(const ModInt rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    constexpr ModInt operator*(const ModInt rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    constexpr ModInt operator/(const ModInt rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }
    constexpr ModInt& operator+=(const ModInt rhs) noexcept {
        n += rhs.n;
        while (n >= M) {
            n -= M;
        }
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt rhs) noexcept {
        n -= rhs.n;
        while (n < 0) {
            n += M;
        }
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt rhs) noexcept {
        (n *= rhs.n) %= M;
        return *this;
    }
    constexpr ModInt& operator/=(ModInt rhs) noexcept {
        int64 a = M - 2;
        while (a) {
            if (a % 2) {
                *this *= rhs;
            }
            rhs *= rhs;
            a /= 2;
        }
        return *this;
    }
};

int64 GCD(int64 a, int64 b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

F reduce(F f) {
    int64 bunbo, bunshi;
    tie(bunshi, bunbo) = f;

    if (bunshi == 0) {
        return F(0, 1);
    }
    int64 g = GCD(abs(bunshi), abs(bunbo));
    bunshi /= g;
    bunbo /= g;
    if (bunbo < 0) {
        bunshi *= -1;
        bunbo *= -1;
    }
    return F(bunshi, bunbo);
}

constexpr int64 MOD = 1e9 + 7;

template <int64 M>
ModInt<M> powMod(ModInt<M> n, int64 a) {
    if (a == 0) return 1;
    if (a & 1) {
        return powMod<M>(n, a - 1) * n;
    } else {
        auto b = powMod<M>(n, a / 2);
        return b * b;
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);

    int n;
    cin >> n;

    int64 num_a_is_zero = 0,
          num_b_is_zero = 0,
          num_both_zero = 0;
    map<F, int64> counter;
    for (int i = 0; i < n; i++) {
        int64 a, b;
        cin >> a >> b;

        if (a == 0 && b == 0) {
            num_both_zero++;
            continue;
        }
        if (a == 0) num_a_is_zero++;
        if (b == 0) num_b_is_zero++;
        if (a != 0 && b != 0) {
            counter[reduce(F(a, b))]++;
        }
    }
    ModInt<MOD> ans = (powMod<MOD>(2, num_a_is_zero) +
                       powMod<MOD>(2, num_b_is_zero) - 1);

    set<F> S;
    for (auto& mp : counter) {
        auto f = mp.first;
        auto f2 = reduce(F(-get<1>(f), get<0>(f)));
        if (S.count(f) || S.count(f2)) continue;

        int64 cnt1 = counter.count(f) ? counter[f] : 0,
                cnt2 = counter.count(f2) ? counter[f2] : 0;
        ans *= (powMod<MOD>(2LL, cnt1) +
                powMod<MOD>(2LL, cnt2) - 1);
        S.insert(f);
        S.insert(f2);
    }
    cout << (ans - 1 + num_both_zero).n << endl;

    return 0;
}

