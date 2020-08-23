// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
#define ednl '\n'
#define endl '\n'
#define sep << ' ' <<
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
using namespace std;
template <typename T>
inline T power(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T tmp = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) tmp = tmp * x % mod;
  return tmp;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T tmp = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) tmp = (tmp + x) % mod;
  return tmp;
}
template <typename T>
inline bool chkmax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  };
  return false;
}
template <typename T>
inline bool chkmin(T &x, const T &y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < v.size(); ++i) os << ' ' << v[i];
  }
  return os;
}
namespace FastInput {
const int SIZE = 1 << 16;
char buf[SIZE], str[60];
int bi = SIZE, bn = SIZE;
inline int read(char *s) {
  while (bn) {
    while (bi < bn && buf[bi] <= ' ') bi++;
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  int sn = 0;
  while (bn) {
    for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];
    if (bi < bn) break;
    bn = fread(buf, 1, SIZE, stdin), bi = 0;
  }
  s[sn] = 0;
  return sn;
}
template <typename T>
inline bool read(T &x) {
  int n = read(str), bf;
  if (!n) return 0;
  int i = 0;
  if (str[i] == '-')
    bf = -1, i++;
  else
    bf = 1;
  T div = 0;
  for (x = 0; i < n; i++) {
    if (str[i] == '.')
      div = 1;
    else
      x = x * 10 + str[i] - '0', div *= 10;
  }
  if (bf < 0) x = -x;
  if (div) x /= div;
  return 1;
}
struct IO {
  template <typename T>
  IO &operator>>(T &__y) {
    read(__y);
    return *this;
  }
} input;
};  // namespace FastInput

int main() {
  quickio;
  int n;
  cin >> n;
  vector<int> arr(n);
  cin >> arr;
  vector<int> B(4);
  cin >> B;
  int ptr = -1;
  if (B[3] == B[2]) ptr = 2;
  if (B[3] == B[1]) ptr = 1;
  if (B[3] == B[0]) ptr = 0;
  int rep[3]{};
  auto check = [&]() -> bool {
    if (B[0] == B[1]) {
      if (arr[rep[0]] != arr[rep[1]]) return false;
    } else {
      if (arr[rep[0]] == arr[rep[1]]) return false;
    }
    if (B[1] == B[2]) {
      if (arr[rep[1]] != arr[rep[2]]) return false;
    } else {
      if (arr[rep[1]] == arr[rep[2]]) return false;
    }
    if (B[0] == B[2]) {
      if (arr[rep[0]] != arr[rep[2]]) return false;
    } else {
      if (arr[rep[0]] == arr[rep[2]]) return false;
    }
    return true;
  };
  vector<vector<int>> cnt(301, vector<int>(n));
  for (int i = n - 1; i >= 0; i--) {
    cnt[arr[i]][i]++;
    if (i == n - 1) continue;
    for (int j = 1; j <= 300; j++) cnt[j][i] += cnt[j][i + 1];
  }
  ll ans = 0;
  for (rep[0] = 0; rep[0] < n - 3; rep[0]++) {
    for (rep[1] = rep[0] + 1; rep[1] < n - 2; rep[1]++) {
      if ((arr[rep[0]] == arr[rep[1]]) != (B[0] == B[1])) continue;
      for (rep[2] = rep[1] + 1; rep[2] < n - 1; rep[2]++) {
        if (!check()) continue;
        if (ptr != -1)
          ans += cnt[arr[rep[ptr]]][rep[2] + 1];
        else {
          ans += n - 1 - rep[2] - cnt[arr[rep[0]]][rep[2] + 1];
          if (arr[rep[1]] != arr[rep[0]]) ans -= cnt[arr[rep[1]]][rep[2] + 1];
          if (arr[rep[2]] != arr[rep[1]] && arr[rep[2]] != arr[rep[0]])
            ans -= cnt[arr[rep[2]]][rep[2] + 1];
        }
      }
    }
  }
  cout << ans << ednl;
  return 0;
}
