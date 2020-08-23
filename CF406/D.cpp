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

int main() {
  quickio;
  int n, q, s;
  cin >> n >> q >> s;
  vector<vector<int>> tree(2, vector<int>(4 * n + 5));
  vector<vector<pii>> G(9 * n);
  int cnt = n;
  function<void(int, int, int)> build = [&](int l, int r, int k) {
    tree[0][k] = ++cnt;
    tree[1][k] = ++cnt;
    if (l == r) {
      G[tree[0][k]].push_back(pii(l, 0));
      G[l].push_back(pii(tree[1][k], 0));
      return;
    }
    int mid = (l + r) >> 1;
    build(mid + 1, r, k << 1 | 1);
    build(l, mid, k << 1);
    G[tree[0][k]].push_back(pii(tree[0][k << 1], 0));
    G[tree[0][k]].push_back(pii(tree[0][k << 1 | 1], 0));
    G[tree[1][k << 1]].push_back(pii(tree[1][k], 0));
    G[tree[1][k << 1 | 1]].push_back(pii(tree[1][k], 0));
  };
  vector<int> buff;
  function<void(int, int, int, int, int, int)> modify =
      [&](int l, int r, int __l, int __r, int chk, int k) {
        if (__l >= l && __r <= r) {
          buff.push_back(tree[chk][k]);
          return;
        }
        int mid = (__l + __r) >> 1;
        if (r > mid) modify(l, r, mid + 1, __r, chk, k << 1 | 1);
        if (l <= mid) modify(l, r, __l, mid, chk, k << 1);
      };
  build(1, n, 1);
  while (q--) {
    int t, u, v, w, l, r;
    cin >> t;
    if (t == 1) {
      cin >> u >> v >> w;
      G[u].push_back(pii(v, w));
    } else {
      cin >> u >> l >> r >> w;
      buff.clear();
      modify(l, r, 1, n, t - 2, 1);
      if (t == 2) {
        for (auto& i : buff) G[u].push_back(pii(i, w));
      } else {
        for (auto& i : buff) G[i].push_back(pii(u, w));
      }
    }
  }
  const ll inf = 1e18;
  vector<ll> dis(9 * n, inf);
  struct ele {
    int node;
    ll w;
    bool operator<(const ele& __y) const { return w > __y.w; }
  };
  std::priority_queue<ele> heap;
  heap.push({s, 0});
  dis[s] = 0;
  while (!heap.empty()) {
    ele cur = heap.top();
    heap.pop();
    if (cur.w != dis[cur.node]) continue;
    for (auto& i : G[cur.node]) {
      if (chkmin(dis[i.first], cur.w + i.second))
        heap.push({i.first, cur.w + i.second});
    }
  }
  for (int i = 1; i <= n; i++) {
    if (i != 1) cout << ' ';
    if (dis[i] == inf)
      cout << -1;
    else
      cout << dis[i];
  }
  return 0;
}