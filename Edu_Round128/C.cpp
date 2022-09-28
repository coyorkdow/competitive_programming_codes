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
  while (T--) {
    string str;
    cin >> str;
    vector<int> pref(str.size());
    vector<int> prefpos(str.size());
    int bal = 0;
    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '0')
        bal--;
      else
        bal++;
      pref[i] = bal;
      // if (i == 0 || pref[i] < pref[prefpos]) {
      //   prefpos = i;
      // }
      prefpos[i] = i;
    }

    vector<int> nums0(str.size()), nums1(str.size());
    for (int i = 0; i < str.size(); i++) {
      if (i) nums0[i] += nums0[i - 1];
      if (str[i] == '0') nums0[i]++;
    }
    for (int i = 0; i < str.size(); i++) {
      if (i) nums1[i] += nums1[i - 1];
      if (str[i] == '1') nums1[i]++;
    }

    for (int i = 1; i < pref.size(); i++) {
      // if (pref[i] > pref[prefpos[i - 1]]) {
      //   prefpos[i] = prefpos[i - 1];
      // }
    }

    int ans = min(nums0[str.size() - 1], nums1[str.size() - 1]);
    int one = 0;
    for (int i = str.size() - 1; i > 0; i--) {
      if (str[i] == '1') one++;
      ans = min(ans, max(one, nums0[i - 1]));

      if (one > nums0[i - 1]) break;

      int diff = nums0[i - 1] - one;
      if (diff == 0) {
        ans = min(ans, one);
      } else {
        ans = min(ans, one + nums1[diff - 1]);
        assert(one + nums1[diff - 1] <= nums0[i - 1] - nums0[diff - 1]);
      }
    }

    for (int i = 0; i < str.size() - 1; i++) {
      ans = min(ans, max(nums1[i], nums0[str.size() - 1] - nums0[i]));
    }

    // cout << pref << endl;
    // cout << prefpos << endl;
    // cout << nums0 << endl;
    // cout << nums1 << endl;

    cout << ans << endl;
  }

  return 0;
}