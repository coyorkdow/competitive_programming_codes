#include <bits/stdc++.h>
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
  // freopen("in", "r", stdin);
  quickio;
  int T;
  cin >> T;
  struct edge {
    int v;
    ll w;
  };

  struct disjoint {
    vector<int> p;
    int find(int x) {
      if (p[x] == -1) p[x] = x;
      return x == p[x] ? x : p[x] = find(p[x]);
    }
    void merge(int u, int v) {
      u = find(u), v = find(v);
      p[v] = u;
    }
    disjoint(int n) : p(vector<int>(n, -1)) {}
  };

  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> G(n);
    map<pair<int, int>, int> PE;
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      if (u == v) continue;
      u--, v--;
      if (u > v) swap(u, v);
      auto key = make_pair(u, v);
      if (PE.count(key))
        PE[key] = min(PE[key], w);
      else
        PE[key] = w;
    }

    int k;
    cin >> k;
    set<int> sp;
    for (int i = 0; i < k; i++) {
      int tmp;
      cin >> tmp;
      sp.insert(--tmp);
    }

    if (n == 2) {
      int ans = INT_MAX;
      for (auto &each : PE){
         chkmin(ans, each.second);
      }
      cout << ans << endl;
      continue;
    }

    set<pair<ll, pair<int, int>>> E, Ano;
    for (auto &each : PE) {
      int u = each.first.first, v = each.first.second;
      if (sp.count(u) && sp.count(v)) continue;
      if (sp.count(u) || sp.count(v))
        Ano.insert(make_pair(each.second, each.first));
      else
        E.insert(make_pair(each.second, each.first));
    }
    disjoint dsu(n);
    int cnt = 0;
    ll ans = 0;
    for (auto &each : E) {
      int u = each.second.first, v = each.second.second;
      u = dsu.find(u), v = dsu.find(v);
      if (u == v) continue;
      dsu.merge(u, v);
      // cout << each.second.first << ' ' << each.second.second << endl;
      cnt++;
      ans += each.first;
    }
    if (cnt != n - k - 1) {
      cout << "Impossible\n";
      continue;
    }
    for (auto &each : Ano) {
      int u = each.second.first, v = each.second.second;
      u = dsu.find(u), v = dsu.find(v);
      if (u == v) continue;
      dsu.merge(u, v);
      // cout << each.second.first << ' ' << each.second.second << endl;
      cnt++;
      ans += each.first;
    }
    if (cnt != n - 1) {
      cout << "Impossible\n";
      continue;
    }
    cout << ans << endl;
  }
  return 0;
}