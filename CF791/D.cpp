#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define FASTIO                         \
  do {                                 \
    std::ios::sync_with_stdio(false);  \
    std::cin.tie(0), std::cout.tie(0); \
  } while (0)
#define ednl '\n'
#define endl '\n'
#define sep << ' ' <<
using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
using pull = std::pair<ull, ull>;
using pll = std::pair<ll, ll>;
template <typename T>
inline T power(T x, T y, T mod = std::numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = std::numeric_limits<T>::max()) {
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

template <class T1, class T2>
inline std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v) {
  is >> v.first >> v.second;
  return is;
}
template <class T1, class T2>
inline std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &v) {
  os << '{' << v.first << ", " << v.second << '}';
  return os;
}

template <template <typename... Args> class ContainerT, typename... Args>
std::ostream &operator<<(std::ostream &os,
                         const ContainerT<Args...> &container) {
  auto it = container.begin();
  if (it != container.end()) {
    os << *it;
    while (++it != container.end()) {
      os << ' ' << *it;
    }
  }
  return os;
}
inline std::ostream &operator<<(std::ostream &__os, const std::string &__str) {
  return std::__ostream_insert(__os, __str.data(), __str.size());
}

template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}

using namespace std;

bool check(const vector<int> &arr, const vector<vector<int>> &G, ll k,
           int target) {
  static vector<int> dep(2e5 + 100);
  static vector<int> vis(2e5 + 100);
  int n = G.size();
  vector<int> deg(n);
  fill(vis.begin(), vis.begin() + n, 0);
  fill(dep.begin(), dep.begin() + n, 0);
  int maxdep = 0;
  bool circle = false;

  for (int i = 0; i < n; i++) {
    if (arr[i] <= target) {
      for (int j : G[i]) {
        deg[j]++;
      }
    }
  }

  bool chk = false;

  function<void(int)> dfs = [&](int cur) {
    vis[cur]++;
    for (int v : G[cur]) {
      if (arr[v] > target) {
        continue;
      }
      if (vis[v]) {
        if (vis[v] == 1) {
          circle = true;
        } else {
          assert(vis[v] == 2);
          dep[cur] = max(dep[cur], dep[v] + 1);
          maxdep = max(maxdep, dep[cur]);
        }
        continue;
      }
      dfs(v);
      dep[cur] = max(dep[cur], dep[v] + 1);
      maxdep = max(maxdep, dep[cur]);
    }
    vis[cur]++;
  };

  for (int i = 0; i < n; i++) {
    if (vis[i] || arr[i] > target) continue;
    if (deg[i]) continue;
    dfs(i);
    if (circle || maxdep >= k - 1) {
      return true;
    }
  }

  for (int i = 0; i < n; i++) {
    if (arr[i] > target) continue;
    if (!vis[i]) {
      chk = true;
      break;
    }
  }

  return chk;
}

int main() {
  // freopen("in", "r", stdin);
  FASTIO;

  int n, m;
  ll k;
  cin >> n >> m >> k;
  vector<int> arr(n);
  cin >> arr;

  vector<vector<int>> G(n);
  // vector<pii> E;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].push_back(v);
    // E.emplace_back(u, v);
  }

  // int l = 1e9 + 10, r = -1;
  // for (int i : arr) {
  //   l = min(l, i);
  //   r = max(r, i);
  // }

  auto sorted = arr;
  sort(all(sorted));
  int l = 0, r = n;

  while (l < r) {
    int mid = (l + r) / 2;
    if (check(arr, G, k, sorted[mid])) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  if (l != n) {
    cout << sorted[l] << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}