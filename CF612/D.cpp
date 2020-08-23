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
#define GG          \
  {                 \
    cout << "NO\n"; \
    exit(0);        \
  }
int main() {
  quickio;
  default_random_engine re;
  uniform_int_distribution<ll> ui(1e9, 1e10);
  re.seed(time(0));
  int n, root;
  cin >> n;
  vector<vector<int>> G(n);
  vector<int> C(n), P(n);
  for (int i = 0; i < n; i++) {
    cin >> P[i] >> C[i];
    P[i]--;
    if (P[i] >= 0)
      G[P[i]].push_back(i);
    else
      root = i;
  }
  vector<int> deg(n);
  queue<int> Q;
  vector<vector<ll>> sub(n);
  vector<ll> ans(n);
  for (int i = 0; i < n; i++) {
    deg[i] = G[i].size();
    if (!deg[i]) Q.push(i);
  }
  ll base = 1e12;
  while (!Q.empty()) {
    int cur = Q.front();
    Q.pop();
    if (sub[cur].size() < C[cur]) GG;
    if (sub[cur].empty()) {
      ans[cur] = base;
      base += ui(re);
    } else {
      if (C[cur] == sub[cur].size())
        ans[cur] = sub[cur].back() + 1e9;
      else if (C[cur] == 0)
        ans[cur] = sub[cur][0] - 1e9;
      else
        ans[cur] = (sub[cur][C[cur]] + sub[cur][C[cur] - 1]) / 2;
      if (P[cur] != -1) {
        vector<ll> tmp(sub[cur].size() + sub[P[cur]].size());
        merge(all(sub[cur]), all(sub[P[cur]]), tmp.begin());
        sub[P[cur]] = tmp;
      }
    }
    if (P[cur] != -1) {
      auto it = lower_bound(all(sub[P[cur]]), ans[cur]);
      sub[P[cur]].insert(it, ans[cur]);
      deg[P[cur]]--;
      if (deg[P[cur]] == 0) Q.push(P[cur]);
    }
  }
  vector<ll> ans2 = ans;
  sort(all(ans2));
  cout << "YES\n";
  for (auto &i : ans)
    cout << (lower_bound(all(ans2), i) - ans2.begin()) + 1 << ' ';
  return 0;
}