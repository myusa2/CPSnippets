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

using int64 = long long;
using uint64 = unsigned long long;

using namespace std;

template <uint64 M>
struct ModInt {
    uint64 n;
    constexpr ModInt(const uint64 n = 0) noexcept : n(n) {}
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

    constexpr ModInt inv() const noexcept {
        return ModInt(1) /= *this;
    }

    constexpr ModInt& operator+=(const ModInt rhs) noexcept {
        n += rhs.n;
        if (n >= M) {
            n -= M;
        }
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt rhs) noexcept {
        n -= rhs.n;
        if (n < 0) {
            n += M;
        }
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt rhs) noexcept {
        (n *= rhs.n) %= M;
        return *this;
    }
    constexpr ModInt& operator/=(ModInt rhs) noexcept {
        int a = M - 2;
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

template <uint64 M>
struct Combination {
    vector<ModInt<M>> fact;
    vector<ModInt<M>> inv_fact;
    
    Combination(int max_n): fact(max_n + 1), inv_fact(max_n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= max_n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        inv_fact[max_n] = fact[max_n].inv();
        for (int i = max_n - 1; i >= 0; i--) {
            inv_fact[i] = inv_fact[i + 1] * (i + 1);
        }
    }

    ModInt<M> choose(int m, int n) {
        if (m < 0 || m < n) return 0;
        // m! / n! / (m - n)!
        return fact[m] * inv_fact[n] * inv_fact[m - n];
    }
};

// a^n mod M を計算
template <uint64 M>
ModInt<M> pow(ModInt<M> a, int n) {
    if (n == 0) return 1;
    if (n % 2 == 0) {
        auto b = pow(a, n / 2);
        return b * b;
    }
    return a * pow(a, n - 1);
}

constexpr uint64 MOD = 998244353;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    Combination<MOD> comb(n);
    // x: 隣り合う組の数
    ModInt<MOD> ans = 0;
    for (int x = 0; x <= k; x++) {
        ans += pow<MOD>(m - 1, n - x - 1) * m * comb.choose(n - 1, x);
    }
    cout << ans.n << endl;

    return 0;
}

