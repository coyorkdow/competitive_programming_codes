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
int main() {
  quickio;
  int n, m;
  cin >> n >> m;
  vector<int> arr(m);
  cin >> arr;
  vector<int> gap(n);
  vector<vector<ll>> pairs(n);
  for (int i = 1; i < m; i++) {
    int u = arr[i - 1], v = arr[i];
    if (u == v) continue;
    if (u > v) swap(u, v);
    pairs[u - 1].push_back(v - 1);
    pairs[v - 1].push_back(u - 1);
    gap[u]++, gap[v - 1]--;
  }
  for (int i = 1; i < n; i++) gap[i] += gap[i - 1];
  assert(gap[0] == 0 && gap.back() == 0);
  ll res = 0;
  vector<ll> contri(n);
  for (int i = 0; i < n; i++) {
    ll tmp = 0;
    for (auto& j : pairs[i]) tmp += abs(i - j);
    sort(all(pairs[i]));
    for (int j = 1; j < pairs[i].size(); j++) pairs[i][j] += pairs[i][j - 1];
    res += tmp;
    contri[i] = tmp;
  }
  res /= 2;
  cout << res << ' ';
  for (int i = 1; i < n; i++) {
    ll ans = res - gap[i] - contri[i];
    int l = 0, r = pairs[i].size();
    while (l < r) {
      int mid = (l + r) / 2;
      ll val = pairs[i][mid];
      if (mid) val -= pairs[i][mid - 1];
      if (val < (ll)i)
        l = mid + 1;
      else
        r = mid;
    }
    if (!pairs[i].empty()) ans += pairs[i].back() + r;
    cout << ans << ' ';
  }
  return 0;
}