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

constexpr uint64 MOD = 1e9 + 7;
constexpr int MAX_N = 200000;

vector<int> tree[MAX_N];
ModInt<MOD> fact[MAX_N], dp1[MAX_N], dp2[MAX_N];
int tree_size[MAX_N];

void firstDFS(int r, int p) {
    tree_size[r] = 1;
    dp1[r] = 1;
    for (int c : tree[r]) {
        if (c == p) continue;

        firstDFS(c, r);
        tree_size[r] += tree_size[c];
        dp1[r] *= dp1[c] / fact[tree_size[c]];
    }
    dp1[r] *= fact[tree_size[r] - 1];
}

void secondDFS(int r, int p, ModInt<MOD> value) {
    int n = tree_size[0];
    dp2[r] = fact[n - 1];
    for (int c : tree[r]) {
        if (c == p) {
            dp2[r] *= value / fact[n - tree_size[r]];
            continue;
        }
        dp2[r] *= dp1[c] / fact[tree_size[c]];
    }

    for (int c : tree[r]) {
        if (c == p) continue;
        secondDFS(c, r, dp2[r] * fact[tree_size[c]] * fact[n - 1 - tree_size[c]] /
                                 (dp1[c] * fact[n - 1]));
    }
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    fact[0] = 1;
    for (int num = 1; num < n; num++) {
        fact[num] = fact[num - 1] * num;
    }

    firstDFS(0, -1);
    secondDFS(0, -1, 1);

    for (int i = 0; i < n; i++) {
        cout << dp2[i].n << endl;
    }

    return 0;
}

