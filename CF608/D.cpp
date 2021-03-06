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
#define GG          \
  {                 \
    cout << "-1\n"; \
    exit(0);        \
  }
int main() {
  quickio;
  int n, m, k;
  cin >> n >> m >> k;
  struct ele {
    int a, b, c;
  };
  vector<ele> arr(n);
  vector<int> rG(n, -1);
  vector<vector<int>> G(n);
  vector<ll> dis, h;
  for (auto &each : arr) cin >> each.a >> each.b >> each.c;
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    // rG[v] = u;
    chkmax(rG[v], u);
  }
  for (int i = 0; i < n; i++) {
    if (rG[i] != -1)
      G[rG[i]].push_back(arr[i].c);
    else
      G[i].push_back(arr[i].c);
  }
  for (auto &each : G) {
    sort(all(each), greater<int>());
    for (int i = 1; i < (int)each.size(); i++) each[i] += each[i - 1];
  }
  vector<vector<int>> dp(n, vector<int>(5001, -1));
  if (k < arr[0].a) GG;
  dp[0][k + arr[0].b] = 0;
  for (int i = 0; i < G[0].size() && k + arr[0].b > i; i++)
    dp[0][k + arr[0].b - i - 1] = G[0][i];
  int last = k + arr[0].b;
  for (int i = 1; i < n; i++) {
    if (last < arr[i].a) GG;
    for (int j = last; j >= arr[i].a && ~dp[i - 1][j]; j--) {
      chkmax(dp[i][j + arr[i].b], dp[i - 1][j]);
      for (int k = 0; k < G[i].size() && j + arr[i].b > k; k++)
        chkmax(dp[i][j + arr[i].b - k - 1], dp[i - 1][j] + G[i][k]);
    }
    last += arr[i].b;
  }
  cout << accumulate(all(dp.back()), -1, [](int x, int y) { return max(x, y); })
       << endl;
  return 0;
}