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
  while (T--) {
    int a, b, k;
    cin >> a >> b >> k;
    if (k == 1) {
      if (a != b && (a % b == 0 || b % a == 0)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
      continue;
    }
    int sum = 0;
    map<int, int> ma, mb;
    auto cal = [&sum](int v, map<int, int> &mp) {
      int sqt = sqrt(v) + 1;
      for (int i = 2; i <= sqt && v > 1; i++) {
        while (v % i == 0) {
          mp[i]++;
          sum++;
          v /= i;
        }
      }
      if (v != 1) {
        mp[v]++;
        sum++;
      }
    };
    cal(a, ma);
    cal(b, mb);
    if (sum >= k) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}