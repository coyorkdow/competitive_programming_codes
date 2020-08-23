// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC
// target("sse,sse2,sse3,ssse3,sse4,popchars,abm,mmx,avx,tune=native")
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
#define reg register
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
  int n;
  cin >> n;
  vector<int> arr(n);
  for (auto &i : arr) cin >> i;
  vector<pii> seq;
  int bg = 0;
  for (int i = 1; i < n; i++) {
    if (arr[i] <= arr[i - 1]) {
      seq.push_back(pii(bg, i - 1));
      bg = i;
    }
  }
  seq.push_back(pii(bg, n - 1));
  int ans = 0;
  for (int i = 0; i < seq.size(); i++) {
    ans = max(ans, seq[i].second - seq[i].first + 1);
    if (i != seq.size()) {
      if (seq[i + 1].first == seq[i].second + 2 &&
          arr[seq[i + 1].first] > arr[seq[i].second])
        ans = max(ans, seq[i].second - seq[i].first + seq[i + 1].second -
                           seq[i + 1].first + 2);
      if (seq[i + 1].first == seq[i].second + 1 &&
          arr[seq[i + 1].first + 1] > arr[seq[i].second])
        ans = max(ans, seq[i].second - seq[i].first + seq[i + 1].second -
                           seq[i + 1].first + 1);
      if (seq[i + 1].first == seq[i].second + 1 &&
          arr[seq[i + 1].first] > arr[seq[i].second - 1])
        ans = max(ans, seq[i].second - seq[i].first + seq[i + 1].second -
                           seq[i + 1].first + 1);
    }
  }
  cout << ans;
  return 0;
}