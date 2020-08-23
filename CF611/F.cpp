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
template <typename T>
inline bool amax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  }
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
#define GG              \
  {                     \
    cout << -1 << endl; \
    exit(0);            \
  }
struct dsu {
  vector<int> f;
  dsu(int n) : f(vector<int>(n, -1)) {}
  int find(int x) {
    if (f[x] == -1) f[x] = x;
    return f[x] == x ? x : f[x] = find(f[x]);
  }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u > v)
      f[v] = u;
    else
      f[u] = v;
  }
};
int main() {
  quickio;
  int n;
  cin >> n;
  dsu DSU(n + 1);
  vector<int> arr(n - 1);
  cin >> arr;
  vector<int> vis(n + 1);
  for (auto &i : arr) vis[i]++;
  struct ele {
    int top_node, biggest_node;
    bool operator<(const ele &__y) const {
      return biggest_node > __y.biggest_node;
    }
  };
  std::priority_queue<ele> heap;
  for (int i = 1; i <= n; i++)
    if (!vis[i]) heap.push(ele{i, i});
  vector<pii> ans;
  while (!heap.empty() && ans.size() != n - 1) {
    int cur = heap.top().top_node;
    heap.pop();
    if (arr.empty()) GG;
    ans.push_back(pii(cur, arr.back()));
    vis[arr.back()]--;
    DSU.merge(cur, arr.back());
    if (!vis[arr.back()]) heap.push(ele{arr.back(), DSU.find(arr.back())});
    arr.pop_back();
  }
  if (ans.size() != n - 1) GG;
  if (heap.size() != 1) GG;
  int siz = 0;
  vector<vector<int>> G(n + 1);
  for (auto &i : ans)
    G[i.first].push_back(i.second), G[i.second].push_back(i.first);
  function<void(int, int)> dfs = [&](int cur, int p) {
    siz++;
    for (auto &i : G[cur])
      if (i != p) dfs(i, cur);
  };
  dfs(1, 0);
  if (siz != n) GG;
  cout << ans.back().second << endl;
  for (auto &i : ans) cout << i.first sep i.second << endl;
  return 0;
}