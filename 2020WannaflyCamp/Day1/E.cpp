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
inline bool amax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  };
  return false;
}
template <typename T>
inline bool amin(T &x, const T &y) {
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
  int n, m;
  cin >> n >> m;
  vector<vector<int>> G(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vector<vector<int>> parents(n, vector<int>(19));
  vector<int> depth(n);
  function<void(int, int)> get_depth = [&](int cur, int p) {
    parents[cur][0] = p;
    if (p != -1) depth[cur] = depth[p] + 1;
    for (auto &i : G[cur]) {
      if (i == p) continue;
      get_depth(i, cur);
    }
  };
  auto get_LCA = [&](int u, int v) -> int {
    if (depth[u] > depth[v]) swap(u, v);
    for (int i = 0; i < 19; i++)
      if (depth[v] - depth[u] >> i & 1) v = parents[v][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; i--) {
      if (parents[u][i] != parents[v][i]) {
        u = parents[u][i];
        v = parents[v][i];
      }
    }
    return parents[u][0];
  };
  get_depth(0, -1);
  for (int i = 1; i < 19; i++) {
    for (int j = 1; j < n; j++)
      if (parents[j][i - 1] == -1)
        parents[j][i] = -1;
      else
        parents[j][i] = parents[parents[j][i - 1]][i - 1];
  }
  vector<ll> diss(n), fix(n);
  vector<ll> ans(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    int LCA = get_LCA(u, v);
    int dis = depth[u] + depth[v] - 2 * depth[LCA];
    diss[u] += 2 * depth[u] - dis + 1;
    diss[v] += 2 * depth[v] - dis + 1;
    // (dis-u+k)*(dis-k)-(dis-u)*dis==2*k*dis-k*dis-k^2
    fix[u] -= 2, fix[v] -= 2;  // 2+4+...+k==k^2+k
    diss[LCA] -= 2 * depth[u] - dis + 1 + 2 * depth[v] - dis + 1;
    fix[LCA] += 4;
    ans[0] += (ll)(depth[u] - depth[LCA]) * (depth[v] - depth[LCA]);
  }
  function<void(int, int)> sum = [&](int cur, int p) {
    for (auto &i : G[cur]) {
      if (i == p) continue;
      sum(i, cur);
      diss[cur] += diss[i];
      fix[cur] += fix[i];
    }
  };
  function<void(int, int)> dfs = [&](int cur, int p) {
    ans[cur] += diss[cur] + fix[cur] * depth[cur];
    for (auto &i : G[cur]) {
      if (i == p) continue;
      ans[i] = ans[cur];
      dfs(i, cur);
    }
  };
  sum(0, -1);
  dfs(0, -1);
  for (auto &i : ans) cout << i << endl;
  return 0;
}