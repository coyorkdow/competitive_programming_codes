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
template <typename W, typename C>
class mcmf {
 private:
#define min(a, b) (a) < (b) ? (a) : (b)
  C inf;
  vector<C>&dis, &h;
  W winf;
  int S, T;
  vector<pair<int, int>> pre;
  vector<vector<int>>& G;
  bitset<(int)2e5> vis;
  static const C eps = (W)1e-9;
  bool dijkstra() {
    __gnu_pbds::priority_queue<heapnode> Q;
    fill(all(dis), inf);
    dis[S] = 0;
    pre[S] = make_pair(-1, -1);
    Q.push(heapnode(S, 0));
    while (!Q.empty()) {
      heapnode cur = Q.top();
      Q.pop();
      if (dis[cur.id] < cur.w) continue;
      for (auto& it : G[cur.id]) {
        edge& e = E[it];
        if (!e.cap) continue;
        C tmp = h[cur.id] + e.cost - h[e.to] + dis[cur.id];
        if (tmp < dis[e.to] - eps) {
          dis[e.to] = tmp;
          pre[e.to] = make_pair(cur.id, it);
          Q.push(heapnode(e.to, tmp));
        }
      }
    }
    return fabs(dis[T] - inf) > eps;
  }
  bool bellman() {
    deque<int> Q;
    fill(all(dis), inf);
    dis[S] = 0;
    pre[S] = make_pair(-1, -1);
    Q.push_back(S);
    vis.set(S);
    while (!Q.empty()) {
      int cur = Q.front();
      Q.pop_front();
      vis.reset(cur);
      for (auto& it : G[cur]) {
        edge& e = E[it];
        if (!e.cap) continue;
        C tmp = e.cost + dis[cur];
        if (tmp < dis[e.to] - eps) {
          dis[e.to] = tmp;
          pre[e.to] = make_pair(cur, it);
          if (vis.test(e.to)) continue;
          vis.set(e.to);
          if (!Q.empty() && dis[Q.front()] < tmp)
            Q.push_back(e.to);
          else
            Q.push_front(e.to);
        }
      }
    }
    vis.reset();
    return fabs(dis[T] - inf) > eps;
  }
  W ex_path() {
    W flow = winf;
    for (auto i = pre[T]; i.first != -1; i = pre[i.first])
      flow = min(flow, E[i.second].cap);
    for (auto i = pre[T]; i.first != -1; i = pre[i.first]) {
      E[i.second ^ 1].cap += flow;
      E[i.second].cap -= flow;
    }
    return flow;
  }

 public:
  int maxn;
  bool negative;
  struct edge {
    int to;
    W cap;
    C cost;
    int id, color;
  };
  vector<edge> E;
  struct heapnode {
    int id;
    C w;
    bool operator<(const heapnode& t) const { return w > t.w; }
    heapnode(int _id, C _w) : id(_id), w(_w) {}
  };
  mcmf(int n, vector<vector<int>>& _g, vector<C>& _dis, vector<C>& _h)
      : dis(_dis), h(_h), G(_g), maxn(n), negative(false) {
    inf = numeric_limits<C>::max() / 2;
    winf = numeric_limits<W>::max() / 2;
    G.assign(n, vector<int>());
    E.clear();
    pre.resize(maxn);
    h.assign(maxn, 0);
    dis.resize(maxn);
  }
  inline int add_edge(const int& u, const int& v, const W& cap, const C& cost,
                      int id = -1, int color = -1) {
    if (cost < 0) negative = true;
    G[u].push_back(E.size());
    G[v].push_back(E.size() + 1);
    E.push_back(edge{v, cap, cost, id, color});
    E.push_back(edge{u, 0, -cost, -1, -1});
    return E.size() - 2;
  }
  pair<C, W> get_mcmf(const int& s, const int& t) {
    S = s, T = t;
    W mf{};
    C mc{};
    W flow;
    if (negative) {
      bellman();
      flow = ex_path();
      for (int i = 0; i < maxn; i++) h[i] = min(h[i] + dis[i], inf);
      mf += flow;
      mc += flow * dis[t];
    }
    while (dijkstra()) {
      flow = ex_path();
      for (int i = 0; i < maxn; i++) h[i] = min(h[i] + dis[i], inf);
      mf += flow;
      mc += flow * h[t];
    }
    return make_pair(mc, mf);
#undef min
  }
};
int main() {
  quickio;
  vector<vector<int>> G;
  vector<int> dis, h;
  int n1, n2, m, r, b;
  cin >> n1 >> n2 >> m >> r >> b;
  mcmf<int, int> cost_flow(n1 + n2 + 5, G, dis, h);
  string A, B;
  cin >> A >> B;
  vector<int> edge;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    if (A[u] == 'R') {
      if (B[v] == 'R')
        edge.push_back(cost_flow.add_edge(u + 1, n1 + v + 1, 1, r, i, 'R'));
      else if (B[v] == 'B') {
        edge.push_back(cost_flow.add_edge(u + 1, v + 1 + n1, 1, r, i, 'R'));
        edge.push_back(cost_flow.add_edge(v + 1 + n1, u + 1, 1, b, i, 'B'));
      } else
        edge.push_back(cost_flow.add_edge(u + 1, 0, 1, r, i, 'R'));
    } else if (A[u] == 'B') {
      if (B[v] == 'R') {
        edge.push_back(cost_flow.add_edge(u + 1, v + 1 + n1, 1, r, i, 'R'));
        edge.push_back(cost_flow.add_edge(v + 1 + n1, u + 1, 1, b, i, 'B'));
      } else if (B[v] == 'B')
        edge.push_back(cost_flow.add_edge(v + 1 + n1, u + 1, 1, b, i, 'B'));
      else
        edge.push_back(cost_flow.add_edge(0, u + 1, 1, b, i, 'B'));
    } else {
      if (B[v] == 'R')
        edge.push_back(cost_flow.add_edge(0, v + 1 + n1, 1, r, i, 'R'));
      else if (B[v] == 'B')
        edge.push_back(cost_flow.add_edge(v + n1 + 1, 0, 1, b, i, 'B'));
    }
  }
  vector<int> in(n1 + n2 + 1);
  for (int i = 0; i < n1; i++) {
    if (A[i] == 'R') {
      in[i + 1]++, in[0]--;
      cost_flow.add_edge(0, i + 1, 1e9, 0);
    } else if (A[i] == 'B') {
      in[i + 1]--, in[0]++;
      cost_flow.add_edge(i + 1, 0, 1e9, 0);
    }
  }
  for (int i = 0; i < n2; i++) {
    if (B[i] == 'R') {
      in[i + n1 + 1]--, in[0]++;
      cost_flow.add_edge(i + n1 + 1, 0, 1e9, 0);
    } else if (B[i] == 'B') {
      in[i + n1 + 1]++, in[0]--;
      cost_flow.add_edge(0, i + n1 + 1, 1e9, 0);
    }
  }
  int tot = 0, S = n1 + n2 + 1, T = n1 + n2 + 2;
  for (int i = 0; i < n1 + n2 + 1; i++) {
    if (in[i] > 0) tot += in[i];
    if (in[i] > 0) cost_flow.add_edge(S, i, in[i], 0);
    if (in[i] < 0) cost_flow.add_edge(i, T, -in[i], 0);
  }
  auto ans = cost_flow.get_mcmf(S, T);
  if (ans.second != tot) {
    cout << "-1\n";
  } else {
    cout << ans.first << endl;
    string _ans(m, 'U');
    for (auto& e : edge) {
      auto& E = cost_flow.E[e];
      if (E.cap) continue;
      if (_ans[E.id] != 'U')
        _ans[E.id] = 'U';
      else
        _ans[E.id] = (char)E.color;
    }
    cout << _ans << endl;
  }
  return 0;
}
