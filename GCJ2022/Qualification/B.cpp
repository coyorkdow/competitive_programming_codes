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

namespace detail {
using std::begin;
using std::declval;
using std::end;

template <class T, class = void>
struct BeginType;

template <class T>
struct BeginType<T, decltype(begin(declval<T>()), ++begin(declval<T>()),
                             (void)*begin(declval<T>()))> {
  using type = decltype(begin(declval<T>()));
};

template <class T, class = void>
struct EndType;

template <class T>
struct EndType<T, decltype(end(declval<T>()), ++end(declval<T>()),
                           (void)*end(declval<T>()))> {
  using type = decltype(begin(declval<T>()));
};

template <class T, class... Args>
auto IsConstructibleImpl(int)
    -> decltype(T(declval<Args>()...), std::true_type{});

template <class T, class...>
auto IsConstructibleImpl(...) -> std::false_type;

}  // namespace detail

template <class T, class = void>
struct IsIterable : public std::false_type {};

template <class T>
struct IsIterable<T, typename std::enable_if<
                         std::is_same<typename detail::BeginType<T>::type,
                                      typename detail::EndType<T>::type>{},
                         void>::type> : public std::true_type {};

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

template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}

template <class T1, class T2>
inline std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &v) {
  os << '{' << v.first << ", " << v.second << '}';
  return os;
}

template <template <typename... Args> class ContainerT, typename... Args>
typename std::enable_if<IsIterable<ContainerT<Args...>>{} &&
                            !std::is_same<ContainerT<Args...>, std::string>{},
                        std::ostream>::type &
operator<<(std::ostream &os, const ContainerT<Args...> &container) {
  auto it = container.begin();
  if (it != container.end()) {
    os << *it;
    while (++it != container.end()) {
      os << ' ' << *it;
    }
  }
  return os;
}

using namespace std;

int main() {
  // freopen("in", "r", stdin);
  FASTIO;
  int T;
  cin >> T;
  for (int _ = 1; _ <= T; _++) {
    cout << "Case #" << _ << ": ";
    int c, m, y, k;
    for (int i = 0; i < 3; i++) {
      if (i == 0)
        cin >> c >> m >> y >> k;
      else {
        int c_, m_, y_, k_;
        cin >> c_ >> m_ >> y_ >> k_;
        chkmin(c, c_);
        chkmin(m, m_);
        chkmin(y, y_);
        chkmin(k, k_);
      }
    }
    if (c + m + y + k < static_cast<int>(1e6)) {
      cout << "IMPOSSIBLE\n";
    } else {
      int left = c + m + y + k - static_cast<int>(1e6);
#define SUBTRACT(col)       \
  if (col > 0) {           \
    int s = min(left, col); \
    col -= s;               \
    left -= s;              \
    continue;               \
  }
      while (left > 0) {
        SUBTRACT(c);
        SUBTRACT(m);
        SUBTRACT(y);
        SUBTRACT(k);
      }
      cout << c << ' ' << m << ' ' << ' ' << y << ' ' << k << '\n';
    }
  }
  return 0;
}