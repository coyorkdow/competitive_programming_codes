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
#define precision(q) std::fixed << std::setprecision(q)
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
  int q = read(str), bf;
  if (!q) return 0;
  int i = 0;
  if (str[i] == '-')
    bf = -1, i++;
  else
    bf = 1;
  T div = 0;
  for (x = 0; i < q; i++) {
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
  vector<vector<int>> G(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    G[u - 1].push_back(v - 1);
    G[v - 1].push_back(u - 1);
  }
  vector<int> dep0(n), pre(n), dep1(n);
  int v0 = 0, v1 = 0;
  function<void(int, int)> dfs0 = [&](int cur, int p) {
    if (p != -1) dep0[cur] = dep0[p] + 1;
    if (dep0[v0] < dep0[cur]) v0 = cur;
    for (auto &i : G[cur]) {
      if (i == p) continue;
      dfs0(i, cur);
    }
  };
  dfs0(0, -1);
  v1 = v0;
  function<void(int, int)> dfs1 = [&](int cur, int p) {
    pre[cur] = p;
    if (p != -1) dep1[cur] = dep1[p] + 1;
    if (dep1[v1] < dep1[cur]) v1 = cur;
    for (auto &i : G[cur]) {
      if (i == p) continue;
      dfs1(i, cur);
    }
  };
  dfs1(v0, -1);
  int v2 = v1, len = 0, temp_len, temp_v2;
  function<void(int, int, int)> dfs2 = [&](int cur, int p, int cnt) {
    if (chkmax(temp_len, cnt)) temp_v2 = cur;
    for (auto &i : G[cur]) {
      if (i == p) continue;
      dfs2(i, cur, cnt + 1);
    }
  };
  int cur = v1, prev = -1;
  while (cur != -1) {
    for (auto &i : G[cur]) {
      if (i == pre[cur] || i == prev) continue;
      temp_len = 0;
      dfs2(i, cur, 1);
      if (chkmax(len, temp_len)) v2 = temp_v2;
    }
    prev = cur;
    cur = pre[cur];
  }
  if (v2 == v1) v2 = pre[v1];
  cout << dep1[v1] + len << endl;
  cout << v0 + 1 sep v1 + 1 sep v2 + 1 << endl;
  return 0;
}