#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define mem(a, x) memset(a, x, sizeof a)
#define precision(n) std::fixed << std::setprecision(n)
#define quickio                     \
  std::ios::sync_with_stdio(false); \
  std::cin.tie(0), std::cout.tie(0)
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
  // freopen("in", "r", stdin);
  quickio;
  int T;
  cin >> T;
  auto cal = [](ull v, vector<int> &hit) {
    for (ull i = 0; (1ull << i) <= v; i++) {
      if (v & (1ull << i)) hit[i] = 1;
    }
  };
  auto ans = [](vector<int> &hit) {
    while (hit.size() && hit.back() == 0) hit.pop_back();
    int ret = hit.size();
    for (int i : hit) ret -= i;
    return ret;
  };
  while (T--) {
    int n;
    ull a[2];
    cin >> n >> a[0] >> a[1];
    vector<int> hit(64);
    cal(a[0], hit);
    cal(a[1], hit);
    int i;
    bool ok = false;
    for (i = 2; i < 30; i++) {
      a[i % 2] = a[(i - 1) % 2] + a[(i - 2) % 2];
      cal(a[i % 2], hit);
      if (n == i) {
        cout << ans(hit) << endl;
        ok = true;
        break;
      }
      if (a[i % 2] > (1ull << 62)) break;
    }
    if (ok) continue;
    cout << ans(hit) << endl;
  }
  return 0;
}