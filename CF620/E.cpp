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
  int Q;
  cin >> Q;
  while (Q--) {
    int x, y, a, b, k;
    cin >> x >> y >> a >> b >> k;
    x--, y--, a--, b--;
    int lca0 = get_LCA(a, b);
    if (depth[a] + depth[b] - 2 * depth[lca0] <= k &&
        (k - depth[a] + depth[b] - 2 * depth[lca0]) % 2 == 0) {
      cout << "YES\n";
    } else {
      int lca1 = get_LCA(a, x), lca2 = get_LCA(b, y);
      int diss = depth[a] + depth[x] - 2 * depth[lca1] + depth[b] + depth[y] -
                 2 * depth[lca2] + 1;
      int diss2 = depth[x] + depth[y] - 2 * depth[get_LCA(x, y)];
      if (diss <= k && (k - diss) % 2 == 0) {
        cout << "YES\n";
      } else {
        int res = k - diss;
        if (res >= diss2 + 1 && ((diss2 + 1) & 1)) {
          cout << "YES\n";
        } else {
          lca1 = get_LCA(a, y), lca2 = get_LCA(b, x);
          diss = depth[a] + depth[x] - 2 * depth[lca1] + depth[b] + depth[y] -
                 2 * depth[lca2] + 1;
          diss2 = depth[x] + depth[y] - 2 * depth[get_LCA(x, y)];
          if (diss <= k && (k - diss) % 2 == 0) {
            cout << "YES\n";
          } else {
            int res = k - diss;
            if (res >= diss2 && ((diss2 + 1) & 1)) {
              cout << "YES\n";
            } else {
              cout << "NO\n";
            }
          }
        }
      }
    }
  }
  return 0;
}