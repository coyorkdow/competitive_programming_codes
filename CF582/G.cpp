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
  T ans = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) ans = ans * x % mod;
  return ans;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
  if (mod == 1) return 0;
  T ans = 0;
  for (T i = 1; i <= y; i <<= 1, x = x * 2 % mod)
    if (i & y) ans = (ans + x) % mod;
  return ans;
}
template <typename T>
inline bool chkmax(T& x, const T& y) {
  if (x < y) {
    x = y;
    return true;
  };
  return false;
}
template <typename T>
inline bool chkmin(T& x, const T& y) {
  if (x > y) {
    x = y;
    return true;
  }
  return false;
}
template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& x : v) is >> x;
  return is;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
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
inline int read(char* s) {
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
inline bool read(T& x) {
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
  IO& operator>>(T& __y) {
    read(__y);
    return *this;
  }
} input;
};  // namespace FastInput
struct dsu {
  vector<int> disjoint, size;
  vector<vector<int>> tree;
  dsu(int n)
      : disjoint(vector<int>(n, -1)),
        size(vector<int>(n)),
        tree(vector<vector<int>>(n)) {}
  int find(int x) {
    if (disjoint[x] == -1) disjoint[x] = x, size[x] = 1;
    return disjoint[x] == x ? x : disjoint[x] = find(disjoint[x]);
  }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (size[u] < size[v]) swap(u, v);
    tree[u].push_back(v);
    disjoint[v] = u;
    size[u] += v;
    size[v] = 0;
  }
};
int main() {
  quickio;
  int n, q;
  cin >> n >> q;
  vector<vector<pii>> G(n);
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }
  vector<int> siz(n);
  vector<bool> centroid(n);
  function<void(int, int)> cal_subtree_size = [&](int cur, int p) {
    siz[cur] = 1;
    for (auto& edge : G[cur]) {
      if (edge.first == p || centroid[edge.first]) continue;
      cal_subtree_size(edge.first, cur);
      siz[cur] += siz[edge.first];
    }
  };
  function<pii(int, int, int)> get_centroid = [&](int cur, int p, int t) {
    pii res = {INT_MAX, -1};
    int s = 1, m = 0;
    for (auto& edge : G[cur]) {
      if (edge.first == p || centroid[edge.first]) continue;
      chkmin(res, get_centroid(edge.first, cur, t));
      chkmax(m, siz[edge.first]);
      s += siz[edge.first];
    }
    chkmax(m, t - s);
    return min(res, pii(m, cur));
  };
  function<void(int, int, int, vector<int>&)> enumerate_path =
      [&](int cur, int p, int w, vector<int>& contain) {
        contain.push_back(w);
        for (auto& edge : G[cur]) {
          if (edge.first == p || centroid[edge.first]) continue;
          enumerate_path(edge.first, cur, max(w, edge.second), contain);
        }
      };
  vector<ll> ans((int)2e5 + 1);
  function<void(int)> slove = [&](int root) {
    cal_subtree_size(root, -1);
    int cen = get_centroid(root, -1, siz[root]).second;
    centroid[cen] = true;
    vector<int> ds;
    for (auto& edge : G[cen]) {
      if (centroid[edge.first]) continue;
      vector<int> tds;
      enumerate_path(edge.first, cen, edge.second, tds);
      sort(all(tds));
      for (int i = 0; i < (int)tds.size(); i++) ans[tds[i]] -= i;
      ds.insert(ds.end(), all(tds));
    }
    sort(all(ds));
    for (int i = 0; i < (int)ds.size(); i++) ans[ds[i]] += i + 1;
    for (auto& edge : G[cen]) {
      if (centroid[edge.first]) continue;
      slove(edge.first);
    }
  };
  slove(0);
  for (int i = 1; i < (int)ans.size(); i++) ans[i] += ans[i - 1];
  vector<int> out(q);
  cin >> out;
  for (auto& i : out) cout << ans[i] << ' ';
  return 0;
}