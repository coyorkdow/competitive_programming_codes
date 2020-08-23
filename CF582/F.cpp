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
  int n, k;
  cin >> n >> k;
  vector<int> pert[2];
  pert[0].resize(n);
  pert[1].resize(n);
  cin >> pert[0] >> pert[1];
  for (int i = 0; i < n; i++) pert[0][i]--, pert[1][i]--;
  vector<int> inj0(n), inj1(n);
  for (int i = 0; i < n; i++) inj0[pert[0][i]] = i, inj1[pert[1][i]] = i;
  dsu DSU(n);
  for (int i = 0; i < n; i++) {
    int u = DSU.find(pert[0][i]), v = DSU.find(pert[1][i]);
    DSU.merge(u, v);
  }
  vector<int> color(n, -1);
  function<void(int, int)> dfs0 = [&](int cur, int root) {
    int mini = pert[0].back(), maxi = pert[0][0];
    queue<int> Q;
    Q.push(cur);
    while (!Q.empty()) {
      int top = Q.front();
      color[top] = color[DSU.find(root)];
      Q.pop();
      if (inj0[top] > inj0[maxi]) maxi = top;
      if (inj0[top] < inj0[mini]) mini = top;
      for (auto& i : DSU.tree[top]) Q.push(i);
    }
    for (int i = inj0[mini]; i <= inj0[maxi]; i++) {
      if (color[pert[0][i]] == color[DSU.find(root)]) continue;
      dfs0(DSU.find(pert[0][i]), root);
    }
    DSU.merge(cur, root);
  };
  int num = 0;
  for (auto& i : pert[0]) {
    if (color[i] != -1) continue;
    color[DSU.find(i)] = num++;
    dfs0(DSU.find(i), DSU.find(i));
  }
  num = 0;
  fill(all(color), -1);
  function<void(int, int)> dfs1 = [&](int cur, int root) {
    int mini = pert[1].back(), maxi = pert[1][0];
    queue<int> Q;
    Q.push(cur);
    while (!Q.empty()) {
      int top = Q.front();
      color[top] = color[DSU.find(root)];
      Q.pop();
      if (inj1[top] > inj1[maxi]) maxi = top;
      if (inj1[top] < inj1[mini]) mini = top;
      for (auto& i : DSU.tree[top]) Q.push(i);
    }
    for (int i = inj1[mini]; i <= inj1[maxi]; i++) {
      if (color[pert[1][i]] == color[DSU.find(root)]) continue;
      dfs1(DSU.find(pert[1][i]), root);
    }
    DSU.merge(cur, root);
  };
  for (auto& i : pert[1]) {
    if (color[i] != -1) continue;
    color[DSU.find(i)] = num++;
    dfs1(DSU.find(i), DSU.find(i));
  }
  if (num < k)
    cout << "NO\n";
  else {
    cout << "YES\n";
    for (int i = 0; i < n; i++)
      cout << static_cast<char>('a' + min(color[i], 25));
    cout << endl;
  }
  return 0;
}