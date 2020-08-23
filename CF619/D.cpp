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
#define GG                  \
  {                         \
    cout << "NO\n" << endl; \
    exit(0);                \
  }
using pis = pair<int, string>;
int main() {
  quickio;
  int T;
  ll n, m, k;
  cin >> n >> m >> k;
  if (n == 1) {
    if (k > 2 * (m - 1)) GG;
    cout << "YES\n";
    // for (int i = 0; i < min(k, m - 1); i++) cout << 'R';
    vector<pis> ans;
    ans.push_back(pis(min(k, m - 1), "R"));
    k -= min(k, m - 1);
    if (k) ans.push_back(pis(k, "L"));
    cout << ans.size() << endl;
    for (auto &each : ans) cout << each.first sep each.second << endl;
    // for (int i = 0; i < k; i++) cout << 'L';
    exit(0);
  }
  if (m == 1) {
    if (k > 2 * (n - 1)) GG;
    cout << "YES\n";
    vector<pis> ans;
    ans.push_back(pis(min(k, n - 1), "D"));
    // for (int i = 0; i < min(k, n - 1); i++) cout << 'D';
    k -= min(k, n - 1);
    // for (int i = 0; i < k; i++) cout << 'U';
    if (k) ans.push_back(pis(k, "U"));
    cout << ans.size() << endl;
    for (auto &each : ans) cout << each.first sep each.second << endl;
    exit(0);
  }
  if (k > 2 * (n - 1) * m + 2 * (m - 1) * n) GG;
  cout << "YES\n";
  vector<pis> ans;
  // for (int i = 0; i < min(k, m - 1); i++) cout << 'R';
  ans.push_back(pis(min(k, m - 1), "R"));
  k -= min(k, m - 1);
  // for (int i = 0; i < min(k, m - 1); i++) cout << 'L';
  if (k) ans.push_back(pis(min(k, m - 1), "L"));
  k -= min(k, m - 1);
  int num = 0;
  while (k) {
    num++;
    // cout << 'D';
    ans.push_back(pis(1, "D"));
    k--;
    if (k == 0) goto out;
    ll res = min(k / 3, m - 1);
    k -= res * 3;
    if (res) ans.push_back(pis(res, "RUD"));
    if (k < 3 && res < m - 1) {
      if (k == 1) ans.push_back(pis(1, "R"));
      if (k == 2) ans.push_back(pis(1, "RU"));
      k = 0;
    }
    if (k == 0) goto out;
    ans.push_back(pis(min(k, m - 1), "L"));
    k -= min(k, m - 1);
    if (k && num == n - 1) {
      ans.push_back(pis(k, "U"));
      k = 0;
    }
  }
out:
  cout << ans.size() << endl;
  for (auto &each : ans) cout << each.first sep each.second << endl;
  exit(0);

  return 0;
}