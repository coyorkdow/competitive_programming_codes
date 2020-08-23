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
template <typename W, typename C>
class mcmf {
 private:
#define min(a, b) (a) < (b) ? (a) : (b)
  C inf, *dis, *h;
  W finf;
  int S, T, size, *ptr;
  vector<vector<int>> &G;
  bitset<1500 * 1500 + 100> vis;
  static const C eps = (W)1e-9;
  bool dijkstra() {
    __gnu_pbds::priority_queue<heapnode> Q;
    memset(dis, 0x4f, sizeof(C) * maxn);
    dis[S] = 0;
    Q.push(heapnode(S, 0));
    while (!Q.empty()) {
      heapnode cur = Q.top();
      Q.pop();
      if (dis[cur.id] < cur.w) continue;
      for (vector<int>::iterator it = G[cur.id].begin(); it != G[cur.id].end();
           it++) {
        edge &e = E[*it];
        if (!e.cap) continue;
        C tmp = h[cur.id] + e.cost - h[e.to] + dis[cur.id];
        if (tmp < dis[e.to] - eps) {
          dis[e.to] = tmp;
          Q.push(heapnode(e.to, tmp));
        }
      }
    }
    return fabs(dis[T] - inf) > eps;
  }
  bool bellman() {
    deque<int> Q;
    memset(dis, 0x4f, sizeof(C) * maxn);
    dis[S] = 0;
    Q.push_back(S);
    vis.set(S);
    while (!Q.empty()) {
      int cur = Q.front();
      Q.pop_front();
      vis.reset(cur);
      for (vector<int>::iterator it = G[cur].begin(); it != G[cur].end();
           it++) {
        edge &e = E[*it];
        if (!e.cap) continue;
        C tmp = e.cost + dis[cur];
        if (tmp < dis[e.to] - eps) {
          dis[e.to] = tmp;
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
  W dfs(int cur, const W flow) {
    if (cur == T) return flow;
    W res = flow, add{};
    vis.set(cur);
    int size = G[cur].size();
    for (; ptr[cur] < size; ptr[cur]++) {
      edge &e = E[G[cur][ptr[cur]]];
      if (!vis.test(e.to) &&
          fabs(dis[cur] + h[cur] + e.cost - h[e.to] - dis[e.to]) <= eps &&
          e.cap) {
        add = dfs(e.to, min(res, e.cap));
        e.cap -= add;
        E[G[cur][ptr[cur]] ^ 1].cap += add;
        res -= add;
        if (res < eps) break;
      }
    }
    vis.reset(cur);
    return flow - res;
  }

 public:
  int maxn;
  bool negative;
  struct edge {
    int to;
    W cap;
    C cost;
  };
  vector<edge> E;
  struct heapnode {
    int id;
    C w;
    bool operator<(const heapnode &t) const { return w > t.w; }
    heapnode(int _id, C _w) : id(_id), w(_w) {}
  };
  mcmf(int n, vector<vector<int>> &_g, int *_ptr, C *_dis, C *_h)
      : dis(_dis),
        h(_h),
        size(0),
        ptr(_ptr),
        G(_g),
        maxn(n),
        negative(false) {
    memset(&inf, 0x4f, sizeof(C));
    memset(&finf, 0x4f, sizeof(W));
  }
  void reset(int n) {
    maxn = n;
    for (register int i = 0; i < n; i++) G[i].clear();
    E.clear();
    memset(ptr, 0, sizeof(int) * maxn);
    memset(h, 0, sizeof(C) * maxn);
    negative = false;
    size = 0;
  }
  inline int add_edge(const int &u, const int &v, const W &cap, const C &cost) {
    if (cost < 0) negative = true;
    G[u].push_back(size++);
    G[v].push_back(size++);
    E.push_back(edge{v, cap, cost});
    E.push_back(edge{u, 0, -cost});
    return size - 2;
  }
  pair<C, W> get_mcmf(const int &s, const int &t) {
    S = s, T = t;
    W mf{};
    C mc{};
    W flow;
    if (negative) {
      bellman();
      memset(ptr, 0, sizeof(int) * maxn);
      flow = dfs(s, finf);
      for (int i = 0; i < maxn; i++) h[i] = min(h[i] + dis[i], inf);
      if (dis[t] > 0) return make_pair(mc, mf);
      mf += flow;
      mc += flow * dis[t];
    }
    while (dijkstra()) {
      memset(ptr, 0, sizeof(int) * maxn);
      flow = dfs(s, finf);
      for (int i = 0; i < maxn; i++) h[i] = min(h[i] + dis[i], inf);
      if (h[t] > 0) return make_pair(mc, mf);
      mf += flow;
      mc += flow * h[t];
    }
    return make_pair(mc, mf);
#undef min
  }
};
ll dis[1500 * 1500 + 10], h[1500 * 1500 + 10];
int ptr[1500 * 1500 + 10];
int main() {
  quickio;
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> id(n, vector<int>(m));
  bitset<1500 * 1500 + 10> vis;
  map<pair<pii, pii>, int> E;
  int num = 0;
  for (int i = 0; i < k; i++) {
    int x1, y1, x2, y2, w;
    cin >> x1 >> y1 >> x2 >> y2 >> w;
    x1--, y1--, x2--, y2--;
    if (!id[x1][y1]) id[x1][y1] = ++num;
    if (!id[x2][y2]) id[x2][y2] = ++num;
    if (id[x1][y1] > id[x2][y2]) {
      swap(x1, x2);
      swap(y1, y2);
    }
    amax(E[{{x1, y1}, {x2, y2}}], w);
  }
  vector<vector<int>> G(num + 2);
  mcmf<int, ll> cost_flow(num + 2, G, ptr, dis, h);
  const int S = 0, T = num + 1;
  for (auto &i : E) {
    int x1 = i.first.first.first, y1 = i.first.first.second;
    int x2 = i.first.second.first, y2 = i.first.second.second;
    int s, t;
    assert(((x1 + y1) & 1) != ((x2 + y2) & 1));
    if ((x1 + y1) & 1)
      s = id[x1][y1], t = id[x2][y2];
    else
      s = id[x2][y2], t = id[x1][y1];
    cost_flow.add_edge(s, t, 1, -i.second);
    if (!vis.test(s)) vis.set(s), cost_flow.add_edge(S, s, 1, 0);
    if (!vis.test(t)) vis.set(t), cost_flow.add_edge(t, T, 1, 0);
  }
  cout << -cost_flow.get_mcmf(S, T).first << endl;
  return 0;
}
