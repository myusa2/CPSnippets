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

constexpr int64 MOD = 1e9 + 7;

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
        *this *= pow(rhs, M - 2);
        return *this;
    }
    constexpr ModInt inv() const noexcept {
        return pow(*this, M - 2);
    }

    static ModInt pow(ModInt a, int64 n) {
        ModInt res = 1;
        while (n) {
            if (n % 2) {
                res *= a;
            }
            a *= a;
            n /= 2;
        }
        return res;
    }
};

namespace CombUtil {

constexpr int64 M = MOD;

vector<ModInt<M>> fact;
vector<ModInt<M>> inv_fact;

static void setup(int max_n) {
    fact.resize(max_n + 1);
    inv_fact.resize(max_n + 1);

    fact[0] = 1;
    for (int n = 1; n <= max_n; n++) {
        fact[n] = fact[n - 1] * n;
    }

    inv_fact[max_n] = fact[max_n].inv();
    for (int n = max_n - 1; n >= 0; n--) {
        inv_fact[n] = inv_fact[n + 1] * (n + 1);
    }
}

ModInt<M> choose(int m, int n) {
    if (m < n) return 0;
    return fact[m] * inv_fact[m - n] * inv_fact[n];
}

};  // namespace CombUtil

namespace CU = CombUtil;

ModInt<CU::M> cumsum(int r, int c) {
    return CU::choose(r + c + 2, r + 1) - CU::choose(r, 0);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    CU::setup(r2 + c2 + 2);

    auto ans = cumsum(r2, c2) - cumsum(r1 - 1, c2) - cumsum(r2, c1 - 1) + cumsum(r1 - 1, c1 - 1);
    cout << ans.n << endl;

    return 0;
}

