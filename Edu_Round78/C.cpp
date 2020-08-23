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
// auto check = [&](int x) -> bool {
//   int l = max(0, n - x);
//   int _bal = 0;
//   for (int i = l; i < l + x; i++)
//     if (arr[i] == 1)
//       _bal--;
//     else
//       _bal++;
//   if (bal - _bal == 0) return true;
//   for (int j = l + 1; j <= n; j++) {
//     if (j + x > 2 * n) break;
//     if (arr[j - 1] == 1)
//       _bal++;
//     else
//       _bal--;
//     if (arr[j + x - 1] == 1)
//       _bal--;
//     else
//       _bal++;
//     if (bal - _bal == 0) return true;
//   }
//   return false;
// };
int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> arr(2 * n);
    vector<int> pref(2 * n);
    cin >> arr;
    map<int, int> cnt;
    int bal = 0, num = 0;
    for (auto &i : arr) {
      if (i == 1)
        bal--;
      else
        bal++;
      if (num < n) cnt[bal] = max(cnt[bal], num);
      pref[num] = bal;
      num++;
    }
    if (bal == 0) {
      cout << 0 << endl;
      continue;
    }
    // bal = -bal;
    int ans = 2 * n;
    for (int i = n - 1; i < 2 * n; i++) {
      int cur = pref[i];
      if (cnt.count(cur - bal)) {
        ans = min(ans, i - cnt[cur - bal]);
      }
      if (cur == bal) ans = min(ans, i + 1);
    }
    cout << ans << endl;
  }
  return 0;
}