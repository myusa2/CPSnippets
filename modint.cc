#include <bits/stdc++.h>

using int64 = long long;
using uint64 = unsigned long long;

using namespace std;

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

    friend ostream& operator<<(ostream& os, const ModInt<M>& m) {
        os << m.n;
        return os;
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

constexpr int MAX_N = 3000;
constexpr int MAX_S = 3000;
constexpr int64 MOD = 998244353;

ModInt<MOD> dp[MAX_N + 1][MAX_S + 1];

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n, s;
    cin >> n >> s;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= s; j++) {
            dp[i + 1][j] += dp[i][j] * 2;
            if (j + a[i] <= s) {
                dp[i + 1][j + a[i]] += dp[i][j];
            }
        }
    }
    cout << dp[n][s] << endl;

    return 0;
}

