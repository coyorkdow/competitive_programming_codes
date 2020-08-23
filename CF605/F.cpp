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
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
template <typename T>
inline T power(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) ans = ans * x % mod;
  return ans;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 0) return 0;
  T ans = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) ans = (ans + x) % mod;
  return ans;
}
template <typename T>
inline T amax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
inline T amin(T &x, const T &y) {
  if (x < y) x = y;
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
using namespace std;
int main() {
  quickio;
  string s, t;
  cin >> s >> t;
  vector<vector<int>> dp[405];
  struct ele {
    int i, j, bal;
    char sym;
  };
  vector<vector<ele>> pre[405];
  int n = 405, inf = 0x3f3f3f3f;
  for (int i = 0; i < n; i++) {
    dp[i].assign(s.length() + 1, vector<int>(t.length() + 1, inf));
    pre[i].assign(s.length() + 1, vector<ele>(t.length() + 1));
  }
  dp[0][0][0] = 0;
  for (int i = 0; i <= s.length(); i++) {
    for (int j = 0; j <= t.length(); j++) {
      for (int k = 0; k < n; k++) {
        if (dp[k][i][j] == inf) continue;
        int newi = i + (i < s.length() && s[i] == '(');
        int newj = j + (j < t.length() && t[j] == '(');
        if (k + 1 < n && dp[k][i][j] + 1 < dp[k + 1][newi][newj]) {
          dp[k + 1][newi][newj] = dp[k][i][j] + 1;
          pre[k + 1][newi][newj] = ele{i, j, k, '('};
        }
        newi = i + (i < s.length() && s[i] == ')');
        newj = j + (j < t.length() && t[j] == ')');
        if (k && dp[k][i][j] + 1 < dp[k - 1][newi][newj]) {
          dp[k - 1][newi][newj] = dp[k][i][j] + 1;
          pre[k - 1][newi][newj] = ele{i, j, k, ')'};
        }
      }
    }
  }
  int i = s.length(), j = t.length(), k = 0;
  for (int t = 0; t < n; t++)
    if (dp[t][i][j] + t < dp[k][i][j] + k) k = t;
  string ans = string(k, ')');
  while (i || j || k) {
    ele &cur = pre[k][i][j];
    ans += cur.sym;
    i = cur.i, j = cur.j, k = cur.bal;
  }
  reverse(all(ans));
  cout << ans;
  return 0;
}