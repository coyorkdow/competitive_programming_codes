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
  //   freopen("in", "r", stdin);
  FASTIO;
  int n;
  cin >> n;
  vector<pll> arr(n);
  cin >> arr;
  //   for (auto &i : arr) cin >> i.first >> i.second;
  sort(all(arr),
       [](const pll &x, const pll &y) { return x.second < y.second; });
  vector<ll> suff(n);
  suff.back() = arr.back().first;
  for (int i = n - 2; i >= 0; i--) suff[i] += suff[i + 1] + arr[i].first;
  ll ans = 0;
  ll tot = 0, sum = 0;
  for (int i = 0; i < n; i++) {
    if (arr[i].second <= tot) {
      ll back = tot - sum;
      auto it = upper_bound(all(suff), back, greater<ll>());
      assert(it != suff.begin());
      int ptr = it - suff.begin();
      ptr--;
      if (ptr > i) {
        ans += arr[i].first;
        tot += arr[i].first;
        sum += arr[i].first;
      } else if (ptr == i) {
        assert(suff[i] >= back);
        ans += suff[i] - back;
        tot += suff[i] - back;
        break;
      } else {
        break;
      }
    } else {
      ll need = arr[i].second - tot;
      ll back = arr[i].second - sum;
      auto it = upper_bound(all(suff), back, greater<ll>());
      int ptr = it - suff.begin();
      ptr--;
      if (ptr > i) {
        ans += arr[i].first + need * 2;
        tot += arr[i].first + need;
        sum += arr[i].first;
      } else if (ptr == i) {
        assert(suff[i] >= back);
        // if (i == n - 1) {
        ans += (suff[i] - back) + need * 2;
        // } else {
        //   ans += (suff[i] - (back - suff[i + 1])) + need * 2;
        // }
        break;
      } else {
        ans += (suff[0] - tot) * 2;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}