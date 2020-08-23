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
#define int long long
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
struct mat {
  vector<vector<int>> M;
  mat(int n, int m) : M(vector<vector<int>>(n, vector<int>(m))) {}
  mat operator*(const mat &__y) const {
    int n = M.size(), m = __y.M[0].size();
    mat ans(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ans.M[i][j] = 0;
        for (int k = 0; k < n; k++) {
          ans.M[i][j] += M[i][k] * __y.M[k][j];
        }
        ans.M[i][j] %= 2;
      }
    }
    return ans;
  }
};
signed main() {
  quickio;
  int n, m, q;
  cin >> n >> m >> q;
  mat v(n, 1), adj(n, n);
  for (int i = 0; i < n; i++) cin >> v.M[i][0];
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj.M[v][u] = 1;
  }
  int cnt = 0;
  mat closure(n, n);
  closure.M = adj.M;
  vector<vector<pll>> rec(n);
  vector<multiset<ll>> query(n);
  vector<pll> out(q);
  for (int i = 0; i < q; i++) {
    int x;
    ll k;
    cin >> x >> k;
    x--;
    out[i] = pll(x, k);
    if (k > 0) query[x].insert(k);
  }
  map<pll, int> ans;
  for (int i = 0; i < n; i++)
    if (v.M[i][0]) {
      rec[i].push_back(pll(1, 0));
    };
  for (int i = 0; i < n; i++) {
    if (query[i].empty()) continue;
    if (rec[i].empty()) continue;
    auto it = query[i].upper_bound(rec[i].back().first);
    if (it == query[i].begin()) continue;
    it--;
    while (true) {
      ans[pll(i, *it)] = cnt;
      if (it == query[i].begin()) {
        query[i].erase(it);
        break;
      }
      query[i].erase(it--);
    }
  }
  cnt++;
  mat nmat = closure * v;
  for (int i = 0; i < n; i++)
    if (nmat.M[i][0]) {
      int pre = rec[i].empty() ? 0 : rec[i].back().first;
      rec[i].push_back(pll(pre + 1, cnt));
    }
  for (int i = 0; i < n; i++) {
    if (query[i].empty()) continue;
    if (rec[i].empty()) continue;
    auto it = query[i].upper_bound(rec[i].back().first);
    if (it == query[i].begin()) continue;
    it--;
    while (true) {
      ans[pll(i, *it)] = cnt;
      if (it == query[i].begin()) {
        query[i].erase(it);
        break;
      }
      query[i].erase(it--);
    }
  }
  map<vector<vector<int>>, int> rep;
  rep[closure.M] = 0;
  int bg = 0;
  while (true) {
    cnt++;
    mat nmat = closure * adj;
    if (rep.count(nmat.M)) {
      bg = rep[nmat.M];
      break;
    }
    rep[nmat.M] = cnt;
    closure.M = nmat.M;
    nmat = closure * v;
    for (int i = 0; i < n; i++)
      if (nmat.M[i][0]) {
        int pre = rec[i].empty() ? 0 : rec[i].back().first;
        rec[i].push_back(pll(pre + 1, cnt));
      }
    for (int i = 0; i < n; i++) {
      if (query[i].empty()) continue;
      if (rec[i].empty()) continue;
      auto it = query[i].upper_bound(rec[i].back().first);
      if (it == query[i].begin()) continue;
      it--;
      while (true) {
        ans[pll(i, *it)] = cnt;
        if (it == query[i].begin()) {
          query[i].erase(it);
          break;
        }
        query[i].erase(it--);
      }
    }
  }
  nmat = closure * v;
  for (auto &each : out) {
    if (each.second <= 0)
      cout << 0 << endl;
    else if (ans.count(each)) {
      cout << ans[each] << endl;
    } else {
      ll tot = each.second;
      int x = each.first;
      assert(rec[x].empty() || rec[x].back().second < tot);
      auto it0 = upper_bound(
          all(rec[x]), pll(0, bg),
          [](pll __x, pll __y) -> bool { return __x.second < __y.second; });
      if (it0 == rec[x].end()) {
        cout << -1 << endl;
        continue;
      }
      ll __ans = 0, bias0 = 0, bias1 = 0;
      if (it0 != rec[x].begin()) {
        __ans += it0[-1].second, tot -= it0[-1].first;
        bias0 = it0[-1].first, bias1 = it0[-1].second;
      }
      __ans += (tot - 1) / (rec[x].back().first - bias0) * (cnt - bg) - 1;
      tot -= (tot - 1) / (rec[x].back().first - bias0) *
             (rec[x].back().first - bias0);
      auto it = lower_bound(
          all(rec[x]), pll(tot + bias0, 1e9),
          [](pll __x, pll __y) -> bool { return __x.first < __y.first; });
      __ans += it->second - bias1;
      cout << __ans << endl;
    }
  }
  // cout << cnt << endl;
  return 0;
}
