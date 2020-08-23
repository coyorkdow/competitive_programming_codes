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
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 1) return 0;
  T res = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) res = (res + x) % mod;
  return res;
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
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> mat(n, vector<int>(m + 1));
  for (auto &each : mat) {
    for (int i = 1; i < each.size(); i++) {
      cin >> each[i];
      each[i] += each[i - 1];
    }
  }
  vector<vector<int>> dp(n, vector<int>(m - k + 2));
  vector<int> pre(m - k + 2), suf(m - k + 2);
  for (int i = 1; i <= m - k + 1; i++) {
    dp[0][i] = mat[0][i + k - 1] - mat[0][i - 1];
    if (n > 1) dp[0][i] += mat[1][i + k - 1] - mat[1][i - 1];
    pre[i] = max(pre[i - 1], dp[0][i]);
  }
  suf.back() = dp[0].back();
  for (int i = m - k; i; i--) {
    suf[i] = max(suf[i + 1], dp[0][i]);
  }
  for (int i = 1; i < n; i++) {
    deque<pii> front, back;
    for (int j = 1; j <= m - k + 1; j++) {
      while (!front.empty() && front.front().second + k <= j) front.pop_front();
      int cur = dp[i - 1][j] - mat[i][j + k - 1];
      while (!front.empty() && front.back().first < cur) front.pop_back();
      front.push_back(pii(cur, j));
      if (j - k > 0) dp[i][j] = pre[j - k];
      if (j + k <= m - k + 1) chkmax(dp[i][j], suf[j + k]);
      chkmax(dp[i][j], front.front().first + mat[i][j - 1]);
    }
    for (int j = m - k + 1; j; j--) {
      while (!back.empty() && back.back().second >= j + k) back.pop_back();
      int cur = dp[i - 1][j] + mat[i][j - 1];
      while (!back.empty() && back.front().first < cur) back.pop_front();
      back.push_front(pii(cur, j));
      chkmax(dp[i][j], back.back().first - mat[i][j + k - 1]);
      dp[i][j] += mat[i][j + k - 1] - mat[i][j - 1];
      if (n > i + 1) dp[i][j] += mat[i + 1][j + k - 1] - mat[i + 1][j - 1];
      if (j == m - k + 1)
        suf[j] = dp[i][j];
      else
        suf[j] = max(suf[j + 1], dp[i][j]);
    }
    for (int j = 1; j <= m - k + 1; j++) pre[j] = max(pre[j - 1], dp[i][j]);
  }
  cout << suf[1] << endl;
  return 0;
}