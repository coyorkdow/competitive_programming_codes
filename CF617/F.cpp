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
  int n;
  cin >> n;
  vector<list<pii>> G(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    G[u].push_back(pii(v, i));
    G[v].push_back(pii(u, i));
  }
  vector<int> dep(n), weight(n - 1, 1), pre(n), preEdge(n);
  function<void(int, int)> dfs = [&](int cur, int p) {
    if (p != -1) dep[cur] = dep[p] + 1;
    pre[cur] = p;
    for (auto it = G[cur].begin(); it != G[cur].end(); it++) {
      if (it->first == p) continue;
      dfs(it->first, cur);
      preEdge[it->first] = it->second;
    }
  };
  dfs(0, -1);
  auto modify = [&](int u, int v, int w) {
    if (dep[u] > dep[v]) swap(u, v);
    while (dep[u] < dep[v]) {
      weight[preEdge[v]] = w;
      v = pre[v];
    }
    while (u != v) {
      weight[preEdge[v]] = w;
      weight[preEdge[u]] = w;
      u = pre[u], v = pre[v];
    }
  };
  auto check = [&](int u, int v, int w) {
    int res = INT_MAX;
    if (dep[u] > dep[v]) swap(u, v);
    while (dep[u] < dep[v]) {
      chkmin(res, weight[preEdge[v]]);
      v = pre[v];
    }
    while (u != v) {
      chkmin(res, weight[preEdge[v]]);
      chkmin(res, weight[preEdge[u]]);
      u = pre[u], v = pre[v];
    }
    return res == w;
  };
  int m;
  cin >> m;
  using piii = pair<pii, int>;
  vector<piii> query(m);
  for (auto &i : query) {
    cin >> i.first.first >> i.first.second >> i.second;
    i.first.first--, i.first.second--;
  }
  sort(all(query), [](piii x, piii y) { return x.second < y.second; });
  for (auto &i : query) modify(i.first.first, i.first.second, i.second);
  for (auto &i : query) {
    if (!check(i.first.first, i.first.second, i.second)) {
      cout << -1 << endl;
      return 0;
    }
  }
  cout << weight << endl;
  return 0;
}