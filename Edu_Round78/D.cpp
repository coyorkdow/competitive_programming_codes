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
template <typename T>
inline void amax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
inline void amin(T &x, const T &y) {
  if (x > y) x = y;
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
class dsu {
 public:
  vector<int> f;
  vector<int> siz;
  dsu(int n) : f(n), siz(n) {}
  int find(int x) {
    if (siz[x] == 0) {
      siz[x] = 1, f[x] = x;
    }
    return f[x] == x ? x : f[x] = find(f[x]);
  }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (siz[u] > siz[v]) swap(u, v);
    f[u] = v, siz[v] += siz[u];
  }
};
int main() {
  quickio;
  int n;
  cin >> n;
  vector<pii> arr(n);
  for (auto &i : arr) cin >> i.first >> i.second;
  sort(all(arr));
  map<int, int> cnt;
  dsu disjoint(n);
  for (int i = 0; i < n; i++) {
    const int fst = arr[i].first, snd = arr[i].second;
    auto it = cnt.upper_bound(fst);
    while (true) {
      if (it == cnt.end() || it->first > snd) break;
      if (disjoint.find(i) == disjoint.find(it->second)) {
        cout << "NO\n";
        return 0;
      }
      disjoint.merge(i, it->second);
      it++;
    }
    cnt[snd] = i;
  }
  for (int i = 1; i < n; i++)
    if (disjoint.find(i) != disjoint.find(0)) {
      cout << "NO\n";
      return 0;
    }
  cout << "YES\n";
  return 0;
}