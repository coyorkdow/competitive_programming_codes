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
template <typename T>
class segment_tree {
 private:
  vector<T> tree;

 public:
  int size;
  segment_tree(int n) : size(n) { tree.resize(4 * n + 5); }
  void modify(const int l, const int r, const T value, int __l = 1,
              int __r = -1, int k = 1) {
    if (__r == -1) __r = size;
    if (__l >= l && __r <= r) {
      tree[k] += value * (__r - __l + 1);
      return;
    }
    int mid = (__l + __r) >> 1;
    if (r > mid) modify(l, r, value, mid + 1, __r, k << 1 | 1);
    if (l <= mid) modify(l, r, value, __l, mid, k << 1);
    tree[k] = min(tree[k << 1], tree[k << 1 | 1]);
  }
  T query(const int l, const int r, int __l = 1, int __r = -1, int k = 1) {
    if (__r == -1) __r = size;
    if (__l >= l && __r <= r) return tree[k];
    int mid = (__l + __r) >> 1;
    T ans = numeric_limits<T>::max();
    if (r > mid) chkmin(ans, query(l, r, mid + 1, __r, k << 1 | 1));
    if (l <= mid) chkmin(ans, query(l, r, __l, mid, k << 1));
    return ans;
  }
};
int main() {
  quickio;
  int T;
  cin >> T;
  while (T--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> arr(n);
    cin >> arr;
    k = min(k, m - 1);
    m -= k;
    int ans = 0;
    for (int i = 0; i <= k; i++) {
      int res = INT_MAX;
      for (int j = 0; j < m; j++) {
        chkmin(res, max(arr[i + j], arr[n - 1 - (k - i) - (m - 1 - j)]));
      }
      chkmax(ans, res);
    }
    cout << ans << endl;
  }
  return 0;
}