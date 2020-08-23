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
bool solve(vector<int> &arr, int &cnt, int tar) {
  if (!cnt) return false;
  vector<pii> li;
  for (int i = 0; i < (int)arr.size(); i++) {
    if (arr[i] == -1) continue;
    li.push_back(pii(i, arr[i]));
  }
  int bg = -2, wid = 1e9;
  for (int i = 0; i < (int)li.size() - 1; i++) {
    if (i + 1 >= li.size()) break;
    if (i == 0 && li[i].second == tar) {
      if (li[i].first > 1) wid = li[i].first, bg = -1;
    }
    if (li[i].second == tar && li[i + 1].second == tar) {
      if (li[i + 1].first - li[i].first > 1 &&
          li[i + 1].first - li[i].first < wid) {
        wid = li[i + 1].first - li[i].first;
        bg = li[i].first;
      }
    }
  }
  if (li.size() && li.back().second == tar) {
    if ((int)arr.size() - li.back().first > 1 &&
        (int)arr.size() - li.back().first < wid)
      bg = li.back().first;
  }
  if (bg != -2) {
    if (bg == -1) {
      for (int i = li[0].first - 1; i >= 0; i--) {
        if (cnt == 0) break;
        arr[i] = tar, cnt--;
      }
    } else
      for (int i = bg + 1; i < (int)arr.size() && arr[i] == -1; i++) {
        if (cnt == 0) break;
        arr[i] = tar, cnt--;
      }
    return true;
  }
  return false;
}
int main() {
  quickio;
  int n;
  cin >> n;
  vector<int> arr(n);
  cin >> arr;
  vector<int> cnt(2);
  for (auto &i : arr) {
    if (!i) continue;
    cnt[i % 2]++;
  }
  vector<int> empty(n);
  {
    int em = 0;
    for (int i = 0; i < n; i++) {
      if (!arr[i]) em++;
      empty[i] = em;
    }
  }
  vector<vector<vector<int>>> dp;
  dp.assign(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 1e9)));
  cnt[0] = n / 2 - cnt[0];
  cnt[1] = (n / 2 + (n & 1)) - cnt[1];
  if (arr[0])
    dp[0][0][0] = 0;
  else {
    if (cnt[0]) dp[0][1][0] = 0;
    if (cnt[1]) dp[0][0][1] = 0;
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= cnt[0]; j++) {
      if (empty[i] < j) break;
      if (arr[i]) {
        if (arr[i - 1]) {
          if (arr[i] % 2 != arr[i - 1] % 2) {
            amin(dp[i][j][0], dp[i - 1][j][0] + 1);
          } else {
            amin(dp[i][j][0], dp[i - 1][j][0]);
          }
        } else {
          if (arr[i] % 2)
            amin(dp[i][j][0], min(dp[i - 1][j][0] + 1, dp[i - 1][j][1]));
          else
            amin(dp[i][j][0], min(dp[i - 1][j][0], dp[i - 1][j][1] + 1));
        }
      } else {
        if (arr[i - 1]) {
          if (arr[i - 1] % 2) {
            if (j) {
              amin(dp[i][j][0], dp[i - 1][j - 1][0] + 1);
            }
            if (cnt[1] && empty[i - 1] - j < cnt[1])
              amin(dp[i][j][1], dp[i - 1][j][0]);
          } else {
            if (j) amin(dp[i][j][0], dp[i - 1][j - 1][0]);
            if (cnt[1] && empty[i - 1] - j < cnt[1])
              amin(dp[i][j][1], dp[i - 1][j][0] + 1);
          }
        } else {
          if (j) {
            amin(dp[i][j][0],
                 min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + 1));
          }
          if (cnt[1] && empty[i - 1] - j < cnt[1])
            amin(dp[i][j][1], min(dp[i - 1][j][0] + 1, dp[i - 1][j][1]));
        }
      }
    }
  }
  cout << min(dp[n - 1][cnt[0]][0], dp[n - 1][cnt[0]][1]) << endl;
  return 0;
}