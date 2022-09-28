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
  // freopen("in", "r", stdin);
  FASTIO;
  int n, q;
  cin >> n >> q;
  map<int, int> R, C;
  fenwick<int> Rbit(n + 1), Cbit(n + 1);
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int x, y;
      cin >> x >> y;
      if (!R.count(x)) {
        Rbit.modify(x, 1);
      }
      if (!C.count(y)) {
        Cbit.modify(y, 1);
      }
      R[x]++;
      C[y]++;
    } else if (t == 2) {
      int x, y;
      cin >> x >> y;
      R[x]--;
      C[y]--;
      if (R[x] == 0) {
        R.erase(x);
        Rbit.modify(x, -1);
      }
      if (C[y] == 0) {
        C.erase(y);
        Cbit.modify(y, -1);
      }
    } else {
      assert(t == 3);
      int x1, x2, y1, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      int l = min(x1, x2), r = max(x1, x2);
      if (Rbit.query(r) - Rbit.query(l - 1) == r - l + 1) {
        cout << "YES\n";
      } else {
        l = min(y1, y2);
        r = max(y1, y2);
        if (Cbit.query(r) - Cbit.query(l - 1) == r - l + 1) {
          cout << "YES\n";
        } else {
          cout << "NO\n";
        }
      }
    }
  }
  return 0;
}