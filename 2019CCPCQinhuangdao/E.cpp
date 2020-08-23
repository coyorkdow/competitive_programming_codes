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
template <typename W>
class max_flow {
 private:
  int maxn, S, T;
  vector<int> dep, ptr;
  const W eps = (W)1e-9;
  vector<vector<int>>& G;
  W inf;
  bool bfs() {
    fill(all(dep), -1);
    queue<int> Q;
    Q.push(S);
    dep[S] = 0;
    while (!Q.empty()) {
      int cur = Q.front();
      Q.pop();
      for (auto& i : G[cur]) {
        edge& e = E[i];
        if (e.cap > eps && dep[e.to] == -1) {
          dep[e.to] = dep[cur] + 1;
          Q.push(e.to);
        }
      }
    }
    return dep[T] != -1;
  }
  W dfs(int cur, const W flow) {
    if (flow < eps) return 0;
    if (cur == T) return flow;
    W add{}, used{};
    for (; ptr[cur] != G[cur].size(); ptr[cur]++) {
      int nowa = G[cur][ptr[cur]];
      if (E[nowa].cap <= eps || dep[E[nowa].to] != dep[cur] + 1) continue;
      add = dfs(E[nowa].to,
                flow - used < E[nowa].cap ? flow - used : E[nowa].cap);
      if (add > eps) {
        used += add;
        E[nowa].cap -= add;
        E[nowa ^ 1].cap += add;
        if (fabs(used - flow) < eps) break;
      }
    }
    return used;
  }

 public:
  struct edge {
    int to;
    W cap;
  };
  vector<edge> E;
  max_flow(int n, vector<vector<int>>& g)
      : maxn(n), G(g), inf(numeric_limits<W>::max() / 2) {
    G.assign(maxn, vector<int>());
    dep.resize(maxn);
    ptr.resize(maxn);
  }
  inline int add_edge(const int& u, const int& v, const W& cap) {
    G[u].push_back(E.size());
    G[v].push_back(E.size() + 1);
    E.push_back(edge{v, cap});
    E.push_back(edge{u, 0});
    return E.size() - 2;
  }
  W get_maxflow(const int s, const int t) {
    S = s, T = t;
    W maxflow{};
    while (bfs()) {
      fill(all(ptr), 0);
      maxflow += dfs(s, inf);
    }
    return maxflow;
  }
};
int main() {
  quickio;
  int T;
  cin >> T;
  int n, m, a, b;
  auto vertpos = [&](int x, int y) { return m * x + y; };
  auto horzpos = [&](int x, int y) { return m * x + y + n * m; };
  while (T--) {
    cin >> n >> m >> a >> b;
    vector<vector<int>> G;
    max_flow<int> flow(n * m * 2 + 2, G);
    vector<string> mat(n);
    for (auto& i : mat) cin >> i;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mat[i][j] == '1') continue;
        if (i && mat[i - 1][j] == '0')
          flow.add_edge(vertpos(i, j), vertpos(i - 1, j), 1);
        if (j && mat[i][j - 1] == '0')
          flow.add_edge(horzpos(i, j), horzpos(i, j - 1), 1);
        if (i + 1 < n && mat[i + 1][j] == '0')
          flow.add_edge(vertpos(i, j), vertpos(i + 1, j), 1);
        if (j + 1 < m && mat[i][j + 1] == '0')
          flow.add_edge(horzpos(i, j), horzpos(i, j + 1), 1);
        flow.add_edge(vertpos(i, j), horzpos(i, j), 1);
        flow.add_edge(horzpos(i, j), vertpos(i, j), 1);
      }
    }
    int S = n * m * 2, T = n * m * 2 + 1;
    for (int i = 0; i < a; i++) {
      int p;
      cin >> p;
      flow.add_edge(S, vertpos(0, p - 1), 1);
    }
    for (int i = 0; i < b; i++) {
      int p;
      cin >> p;
      flow.add_edge(vertpos(n - 1, p - 1), T, 1);
    }
    if (flow.get_maxflow(S, T) == a)
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}