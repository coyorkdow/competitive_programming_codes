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
#define sep << ' ' <<
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::pair<ull, ull> pull;
typedef std::pair<ll, ll> pll;
using namespace std;
template <typename T>
inline T power(T x, T y, T mod = numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = numeric_limits<T>::max()) {
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

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<vector<int>> G(n + 1);
  set<pii> edges;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    edges.insert({u, v});
    edges.insert({v, u});
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vector<int> dep(n + 1), pre(n + 1);
  function<void(int, int)> dfs0 = [&](int cur, int p) {
    dep[cur] = dep[p] + 1;
    pre[cur] = p;
    for (int v : G[cur]) {
      if (v == p) continue;
      dfs0(v, cur);
    }
  };
  set<int> sub;
  function<void(int, int, int)> dfs1 = [&](int cur, int p, int lca) {
    sub.insert(cur);
    for (int v : G[cur]) {
      if (v == p || v == lca) continue;
      dfs1(v, cur, lca);
    }
  };
  while (true) {
    fill(all(dep), 0);
    int u, v;
    for (int i = 1; i <= n; i++) {
      if (!G[i].empty()) {
        dfs0(i, 0);
        u = i, v = i;
        break;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (dep[i] > dep[u]) u = i;
    }
    dep[u] = 0;
    dfs0(u, 0);
    for (int i = 1; i <= n; i++) {
      if (dep[i] > dep[v]) v = i;
    }
    cout << '?' sep u sep v << endl;
    int lca;
    cin >> lca;
    if (lca == u || lca == v) {
      cout << '!' sep lca << endl;
      exit(0);
    }
    int cur = v;
    set<int> path;
    while (cur != u) {
      path.insert(cur);
      if (cur == lca && G[cur].size() < 3) {
        cout << '!' sep lca << endl;
        exit(0);
      }
      cur = pre[cur];
    }
    path.insert(u);
    if (!path.count(lca)) {
      cout << '!' sep lca << endl;
      exit(0);
    }
    sub.clear();
    dfs1(u, 0, lca);
    dfs1(v, 0, lca);
    for (auto &i : G) i.clear();
    for (auto it = edges.begin(); it != edges.end();) {
      auto i = *it;
      if (sub.count(i.first) || sub.count(i.second)) {
        it = edges.erase(it);
      } else {
        G[i.first].push_back(i.second);
        it++;
      }
    }
  }
  return 0;
}