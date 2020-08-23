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
inline T power(T x, T y, T mod = numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = numeric_limits<T>::max()) {
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
tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
     tree_order_statistics_node_update>
    rbTree;
using namespace std;
template <typename T>
class fenwick {
 public:
  vector<T> arr;
  int n;
  fenwick(int _n) : n(_n) { arr.resize(n); }
  void modify(int x, T v) {
    while (x < n) {
      arr[x] += v;
      x |= (x + 1);
    }
  }
  T query(int x) {
    T v{};
    while (x >= 0) {
      v += arr[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, q;
  cin >> n >> q;
  fenwick<int> bit(n + 1);
  int tmp;
  for (int i = 0; i < n; i++) {
    cin >> tmp;
    bit.modify(tmp, 1);
  }
  while (q--) {
    cin >> tmp;
    if (tmp > 0) {
      bit.modify(tmp, 1);
    } else {
      int l = 0, r = n;
      tmp = -tmp;
      while (l < r) {
        int mid = (r + l) / 2;
        int v = bit.query(mid);
        if (tmp > v)
          l = mid + 1;
        else
          r = mid;
      }
      bit.modify(l, -1);
    }
  }
  if (bit.query(n) == 0)
    cout << 0;
  else {
    for (int i = 1; i <= n; i++) {
      if (bit.query(i) != 0) {
        cout << i;
        break;
      }
    }
  }
  return 0;
}