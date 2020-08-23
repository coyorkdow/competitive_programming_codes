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
#define mem(g, x) memset(g, x, sizeof g)
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
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = (int)1e9 + 7) {
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

int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    ll n, m;
    cin >> n >> m;
    map<ll, int> boxes;
    for (int i = 0; i < m; i++) {
      ll tmp;
      cin >> tmp;
      boxes[tmp]++;
    }
    set<ll> res;
    for (ll i = 0; (1ll << i) <= n; i++) {
      if ((n & (1ll << i)) == 0) continue;
      auto it = boxes.find(1ll << i);
      if (it != boxes.end()) {
        it->second--;
        if (it->second == 0) boxes.erase(it);
        n -= (1ll << i);
      } else
        res.insert(1ll << i);
    }
    int ans = 0;
    int T = 1000;
    while (T-- && !res.empty() && !boxes.empty()) {
      for (auto each = boxes.begin(); each != boxes.end();) {
        if (each->first < *res.begin()) {
          if (each->second >= 2) boxes[each->first * 2] += each->second / 2;
          boxes.erase(each);
          break;
        } else if (res.count(each->first)) {
          res.erase(each->first);
          each->second--;
          if (each->second == 0) each = boxes.erase(each);
        } else {
          ll tmp = each->first, num = each->second;
          while (!res.empty() && *res.begin() < tmp && !res.count(tmp)) {
            ans++;
            boxes[tmp]--;
            boxes[tmp / 2] += 2;
            tmp /= 2;
          }
          if (res.count(tmp)) {
            res.erase(tmp);
            boxes[tmp]--;
          }
          if (boxes[tmp] == 0) boxes.erase(tmp);
          break;
        }
      }
    }
    if (res.empty())
      cout << ans << endl;
    else
      cout << -1 << endl;
  }
  return 0;
}