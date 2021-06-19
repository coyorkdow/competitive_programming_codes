#include <bits/stdc++.h>
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

int main() {
//   freopen("in", "r", stdin);
  quickio;
  int T;
  cin >> T;
  //   if (T == 10000) {
  //     for (int i = 1; i <= T; i++) {
  //       ll x, y, a, b;
  //       cin >> x >> y >> a >> b;
  //       if (i == 5822) {
  //         cout << x sep y sep a sep b << endl;
  //       }
  //     }
  //   }

  auto cal0 = [](ll n, ll m, ll a, ll b) {
    ll D = (a - b) * a - (b - a) * b;
    ll x = (n * a - b * m) / D;
    ll y = ((a - b) * m - (b - a) * n) / D;
    return x;
  };

  while (T--) {
    ll x, y, a, b;
    cin >> x >> y >> a >> b;
    if (x < y) swap(x, y);
    if (a < b) swap(a, b);
    if (a == b) {
      cout << y / a << endl;
      continue;
    }
    // for gift which contains a red candies and b blue candies.
    // how many of such gifts.
    int l = 0, r = x / a;
    chkmin(r, (int)(y / b));
    int v = cal0(x, y, a, b);
    auto cal1 = [&](int v) {
      int xrest = x - v * a;
      int yrest = y - v * b;
      int num = min(xrest / b, yrest / a);
      return v + num;
    };
    int ans = 0;
    for (int i = max(0, min(r, v - 10)); i <= min(r, v + 10); i++) {
      chkmax(ans, cal1(i));
    }
    cout << ans << endl;
  }
  return 0;
}