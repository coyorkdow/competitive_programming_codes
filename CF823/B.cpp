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
  cin >> T;
  struct ele {
    double val;
    int id;
    int endpoint;
    bool operator<(const ele &y) const { return val < y.val; }
  };

  while (T--) {
    int n;
    cin >> n;
    vector<int> X(n), Y(n);
    cin >> X >> Y;
    vector<pair<int, double>> arr;
    arr.reserve(2 * n);
    vector<ele> coord(2 * n);
    double l = 0, r = 1e9;
    for (auto i : Y) l = max(l, double(i));

    auto doit = [&](double mid) -> int {
      for (int i = 0; i < n; i++) {
        coord[i * 2] = ele{X[i] - (mid - Y[i]), i, 0};
        coord[i * 2 + 1] = ele{X[i] + (mid - Y[i]), i, 1};
        // cout << coord[i * 2].val << ' ' << coord[i * 2 + 1].val << endl;
      }
      sort(all(coord));
      arr.clear();
      for (int i = 0; i < 2 * n; i++) {
        if (i && coord[i].val == coord[i - 1].val) {
        } else {
          arr.emplace_back(0, coord[i].val);
          if (coord[i - 1].endpoint == 1) {
            arr.back().first--;
          }
        }
        if (coord[i].endpoint == 0) {
          arr.back().first++;
        }
      }
      // cout << arr << endl;
      int cnt = 0;
      for (int i = 1; i < arr.size(); i++) {
        arr[i].first += arr[i - 1].first;
        cnt = max(cnt, arr[i].first);
      }
      return cnt;
    };

    while (r - l >= 1e-6) {
      double mid = (l + r) / 2.0;
      int cnt = doit(mid);
      if (cnt == n) {
        r = mid;
      } else {
        l = mid;
      }
    }

    int cnt = doit(r);
    assert(cnt == n);
    double ans;
    for (int i = 0; i < arr.size(); i++) {
      if (arr[i].first == n) {
        ans = arr[i].second;
        break;
      }
    }
    cout << precision(6) << ans << endl;
  }

  return 0;
}