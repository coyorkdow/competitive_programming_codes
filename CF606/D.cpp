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
inline T amax(T &x, const T &y) {
  if (x < y) x = y;
}
template <typename T>
inline T amin(T &x, const T &y) {
  if (x > y) x = y;
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
using namespace std;
int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    map<string, int> cnt;
    for (int i = 0; i < n; i++) {
      string t;
      cin >> t;
      cnt[t] = i + 1;
    }
    int _00 = 0, _01 = 0, _11 = 0, _10 = 0;
    vector<pair<string, int>> sp;
    int num;
    for (auto &i : cnt) {
      if (i.first[0] == '0') {
        if (i.first.back() == '0')
          _00++;
        else
          _01++;
      } else {
        if (i.first.back() == '0')
          _10++;
        else
          _11++;
      }
      string t = i.first;
      reverse(all(t));
      if (!cnt.count(t)) {
        sp.push_back(make_pair(i.first, i.second));
      }
    }
    // sort(all(sp));
    int sp_00 = 0, sp_01 = 0, sp_11 = 0, sp_10 = 0;
    for (auto &j : sp) {
      auto &i = j.first;
      if (i[0] == '0') {
        if (i.back() == '0')
          sp_00++, i = "00";
        else
          sp_01++, i = "01";
      } else {
        if (i.back() == '0')
          sp_10++, i = "10";
        else
          sp_11++, i = "11";
      }
    }
    if ((_01 || _10) && abs(_01 - _10) <= 1) {
      cout << 0 << endl << endl;
      continue;
    }
    if (!(_01 || _10) && _00 && _11) {
      cout << -1 << endl;
      continue;
    }
    int diss = abs(_01 - _10) - 1;
    vector<int> ans;
    num = 0;
    if (_01 < _10) {
      for (auto &i : sp) {
        if (i.first == "10") ans.push_back(i.second), num += 2;
        if (num >= diss) break;
      }
    }
    if (_10 < _01) {
      if (sp_01 >= diss) ans;
      for (auto &i : sp) {
        if (i.first == "01") ans.push_back(i.second), num += 2;
        if (num >= diss) break;
      }
    }
    if (num >= diss) {
      cout << ans.size() << endl;
      for (auto &i : ans) cout << i << ' ';
      cout << endl;
    } else
      cout << -1 << endl;
  }
  return 0;
}
// 10,01 00,01
// 01,10