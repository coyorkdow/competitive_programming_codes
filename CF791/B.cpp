#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define FASTIO                         \
  do {                                 \
    std::ios::sync_with_stdio(false);  \
    std::cin.tie(0), std::cout.tie(0); \
  } while (0)
#define ednl '\n'
#define endl '\n'
#define sep << ' ' <<
using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
using pull = std::pair<ull, ull>;
using pll = std::pair<ll, ll>;
template <typename T>
inline T power(T x, T y, T mod = std::numeric_limits<T>::max()) {
  if (mod == 1) return 0;
  T res = 1;
  for (T i = 1; i <= y; i <<= 1, x = x * x % mod)
    if (i & y) res = res * x % mod;
  return res;
}
template <typename T>
inline T mul(T x, T y, T mod = std::numeric_limits<T>::max()) {
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

template <class T1, class T2>
inline std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v) {
  is >> v.first >> v.second;
  return is;
}
template <class T1, class T2>
inline std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &v) {
  os << '{' << v.first << ", " << v.second << '}';
  return os;
}

template <template <typename... Args> class ContainerT, typename... Args>
std::ostream &operator<<(std::ostream &os,
                         const ContainerT<Args...> &container) {
  auto it = container.begin();
  if (it != container.end()) {
    os << *it;
    while (++it != container.end()) {
      os << ' ' << *it;
    }
  }
  return os;
}
inline std::ostream &operator<<(std::ostream &__os, const std::string &__str) {
  return std::__ostream_insert(__os, __str.data(), __str.size());
}

template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}

using namespace std;

int main() {
  // freopen("in", "r", stdin);
  FASTIO;
  int T;
  // // cin >> T;
  // while (T--) {
  int n, q;
  cin >> n >> q;
  vector<ll> arr(n);
  cin >> arr;
  ll sum = 0;
  for (auto i : arr) sum += i;
  map<int, ll> rec;
  ll rep = -1;
  while (q--) {
    ll t, I, x;
    cin >> t;
    if (t == 1) {
      cin >> I >> x;
      if (rec.count(I)) {
        sum += x - rec[I];
        rec[I] = x;
      } else {
        if (rep == -1) {
          sum += x - arr[I - 1];
          rec[I] = x;
        } else {
          sum += x - rep;
          rec[I] = x;
        }
      }
      cout << sum << endl;
    } else {
      cin >> x;
      rep = x;
      cout << x * n << endl;
      sum = x * n;
      rec.clear();
    }
  }
  // }

  return 0;
}