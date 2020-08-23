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
template <typename T>
inline bool amax(T &x, const T &y) {
  if (x < y) {
    x = y;
    return true;
  }
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
  int n;
  cin >> n;
  vector<int> arr(n);
  cin >> arr;
  sort(all(arr));
  vector<vector<int>> dp(n, vector<int>(3));
  vector<vector<int>> occupied(3, vector<int>(n + 2));
  for (auto &i : dp[0]) i = 1;
  occupied[0][arr[0] - 1]++;
  occupied[1][arr[0]]++;
  occupied[2][arr[0] + 1]++;
  for (int i = 1; i < n; i++) {
    int flag[3];
    for (int j = 0; j < 3; j++) {
      if (occupied[j][arr[i]]) {
        if (amax(dp[i][1], dp[i - 1][j])) flag[1] = j;
      } else {
        if (amax(dp[i][1], dp[i - 1][j] + 1)) flag[1] = j;
      }
      if (occupied[j][arr[i] - 1]) {
        if (amax(dp[i][0], dp[i - 1][j])) flag[0] = j;
      } else {
        if (amax(dp[i][0], dp[i - 1][j] + 1)) flag[0] = j;
      }
      if (occupied[j][arr[i] + 1]) {
        if (amax(dp[i][2], dp[i - 1][j])) flag[2] = j;
      } else {
        if (amax(dp[i][2], dp[i - 1][j] + 1)) flag[2] = j;
      }
    }
    int tmp[3][3];
    for (int j = 0; j < 3; j++)
      for (int k = -1; k < 2; k++) tmp[j][k + 1] = occupied[j][arr[i] + k];
    for (int j = 0; j < 3; j++) {
      for (int k = -1; k < 2; k++)
        occupied[j][arr[i] + k] = tmp[flag[j]][k + 1];
    }
    occupied[0][arr[i] - 1]++;
    occupied[1][arr[i]]++;
    occupied[2][arr[i] + 1]++;
  }
  int _max = max(dp.back()[0], max(dp.back()[1], dp.back()[2]));
  for (int i = 0; i < 3; i++) fill(all(occupied[i]), 0);
  for (auto &i : dp) fill(all(i), INT_MAX);
  for (auto &i : dp[0]) i = 1;
  occupied[0][arr[0] - 1]++;
  occupied[1][arr[0]]++;
  occupied[2][arr[0] + 1]++;
  for (int i = 1; i < n; i++) {
    int flag[3];
    for (int j = 0; j < 3; j++) {
      if (occupied[j][arr[i]]) {
        if (amin(dp[i][1], dp[i - 1][j])) flag[1] = j;
      } else {
        if (amin(dp[i][1], dp[i - 1][j] + 1)) flag[1] = j;
      }
      if (occupied[j][arr[i] - 1]) {
        if (amin(dp[i][0], dp[i - 1][j])) flag[0] = j;
      } else {
        if (amin(dp[i][0], dp[i - 1][j] + 1)) flag[0] = j;
      }
      if (occupied[j][arr[i] + 1]) {
        if (amin(dp[i][2], dp[i - 1][j])) flag[2] = j;
      } else {
        if (amin(dp[i][2], dp[i - 1][j] + 1)) flag[2] = j;
      }
    }
    int tmp[3][3];
    for (int j = 0; j < 3; j++)
      for (int k = -1; k < 2; k++) tmp[j][k + 1] = occupied[j][arr[i] + k];
    for (int j = 0; j < 3; j++) {
      for (int k = -1; k < 2; k++)
        occupied[j][arr[i] + k] = tmp[flag[j]][k + 1];
    }
    occupied[0][arr[i] - 1]++;
    occupied[1][arr[i]]++;
    occupied[2][arr[i] + 1]++;
  }
  int _min = min(dp.back()[0], min(dp.back()[1], dp.back()[2]));
  cout << _min << endl << _max << endl;
  return 0;
}